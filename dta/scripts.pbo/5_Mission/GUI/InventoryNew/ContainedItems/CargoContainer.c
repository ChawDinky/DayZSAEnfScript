class CargoContainer extends Container
{
	protected const int ROWS_NUMBER_XBOX = 5;
	
	protected EntityAI												m_Entity;
	protected CargoBase												m_Cargo;
	
	protected int													m_FocusedItemPosition = -1;
	protected ref array<ref CargoContainerRow>						m_Rows;
	protected ref array<ref Icon>									m_Icons;
	protected ref map<EntityAI, ref Param3<ref Icon, int, int>>		m_ShowedItemPositions;
	
	protected float													m_IconSize;
	protected float													m_SpaceSize;
	
	protected bool													m_IsAttachment;
	protected Widget												m_CargoHeader;
	protected Widget												m_CargoContainer;
	protected Widget												m_ItemsContainer;
	protected ref SizeToChild										m_Resizer1;
	protected ref SizeToChild										m_Resizer2;
	
	void CargoContainer( LayoutHolder parent, bool is_attachment = false )
	{
		m_IsAttachment			= is_attachment;
		m_Rows					= new array<ref CargoContainerRow>;
		m_Icons					= new array<ref Icon>;
		m_ShowedItemPositions	= new map<EntityAI, ref Param3<ref Icon, int, int>>;
		
		m_CargoContainer		= m_RootWidget.FindAnyWidget( "grid_background" );
		m_ItemsContainer		= m_RootWidget.FindAnyWidget( "grid_overlay" );
		m_CargoHeader			= m_RootWidget.FindAnyWidget( "grid_container_header_spacer" );
		
		m_RootWidget.GetScript( m_Resizer1 );
		
		m_RootWidget.FindAnyWidget( "grid_container" ).GetScript( m_Resizer2 );
		m_CargoHeader.Show( is_attachment );
		
		m_MainWidget			= m_CargoContainer;
		m_FocusedItemPosition	= -1;
	}
	
	override void SetLayoutName()
	{
		#ifdef PLATFORM_CONSOLE
			m_LayoutName = WidgetLayoutName.CargoContainerXbox;
		#else
			switch( InventoryMenu.GetWidthType() )
			{
				case ScreenWidthType.NARROW:
				{
					m_LayoutName = WidgetLayoutName.CargoContainerNarrow;
					break;
				}
				case ScreenWidthType.MEDIUM:
				{
					m_LayoutName = WidgetLayoutName.CargoContainerMedium;
					break;
				}
				case ScreenWidthType.WIDE:
				{
					m_LayoutName = WidgetLayoutName.CargoContainerWide;
					break;
				}
			}
		#endif
			
	}
	
	void SetEntity( EntityAI item )
	{
		if( item )
		{
			m_Entity		= item;
			
			InitGridHeight();
			
			m_Cargo			= item.GetInventory().GetCargo();
			m_MainWidget	= m_ItemsContainer;
			
			UpdateHeaderText();
		}
	}
	
	void UpdateHeaderText()
	{
		Widget header;
		string name = m_Entity.GetDisplayName();
		name.ToUpper();
		
		if( m_Entity.GetInventory().GetCargo() )
		{
			name = name + " (" + GetCargoCapacity().ToString() + "/" + GetMaxCargoCapacity() + ")";
			if( m_IsAttachment && m_CargoHeader )
			{
				header = m_CargoHeader;
			}
			else if( GetParent().GetRootWidget().FindAnyWidget( "hands_item_header" ) )
			{
				header = GetParent().GetRootWidget().FindAnyWidget( "hands_item_header" );
			}
			else
			{
				header = GetParent().GetRootWidget().FindAnyWidget( "closable_header_root" );
			}
			
			if( header )
				TextWidget.Cast( header.FindAnyWidget( "TextWidget0" ) ).SetText( name );
		}
		else
		{
			TextWidget.Cast( header.FindAnyWidget( "TextWidget0" ) ).SetText( name );
		}
	}
	
	void InitGridHeight()
	{
		m_Rows.Clear();
		m_ShowedItemPositions.Clear();
		
		ref CargoContainerRow row;
		
		#ifdef PLATFORM_CONSOLE
		int cargo_height = 	1;
		#else
		int cargo_height = 	m_Entity.GetInventory().GetCargo().GetHeight();
		#endif
		
		for ( int j = 0; j < cargo_height; j++ )
		{
			row = new CargoContainerRow( this );
			
			row.SetNumber( j );
			row.SetEntity( m_Entity );
			
			#ifdef PLATFORM_WINDOWS
			#ifndef PLATFORM_CONSOLE
			row.SetWidth( m_Entity.GetInventory().GetCargo().GetWidth() );
			#endif
			#endif
			
			row.GetRootWidget().SetSort( j );
			m_Rows.Insert( row );
		}
		
		float y;
		row.GetRootWidget().FindAnyWidget( "Icon0" ).GetScreenSize( y, m_IconSize );
		#ifdef PLATFORM_WINDOWS
		#ifndef PLATFORM_CONSOLE
			row.GetRootWidget().FindAnyWidget( "Spacer0" ).GetScreenSize( m_SpaceSize, y );
		#endif
		#endif
		
		m_Resizer2.ResizeParentToChild();
		m_Resizer1.ResizeParentToChild();
	}
	
	float GetIconSize()
	{
		return m_IconSize;
	}
	
	float GetSpaceSize()
	{
		return m_SpaceSize;
	}
	
	int GetCargoCapacity()
	{
		#ifdef PLATFORM_CONSOLE
		#ifndef PLATFORM_WINDOWS
			return CargoList.Cast( m_Cargo ).GetTotalWeight( null );
		#endif
		#endif
		int total_size = 0;
		for( int i = 0; i < m_Cargo.GetItemCount(); i++ )
		{
			int x, y;
			m_Cargo.GetItemSize( i, x, y );
			total_size += x * y;
		}
		return total_size;
	}
	
	int GetMaxCargoCapacity()
	{
		#ifdef PLATFORM_CONSOLE
		#ifndef PLATFORM_WINDOWS
			return CargoList.Cast( m_Cargo ).GetMaxWeight();
		#endif
		#endif
		return m_Cargo.GetWidth() * m_Cargo.GetHeight();
	}
	
	Icon GetIcon( EntityAI item )
	{
		if( item && m_ShowedItemPositions.Contains( item ) )
		{
			Param3<ref Icon, int, int> data = m_ShowedItemPositions.Get( item );
			return data.param1;
		}
		return null;
	}
	
	Icon GetIcon( int index )
	{
		if( index >= 0 && m_Cargo.GetItemCount() > index )
			return GetIcon( m_Cargo.GetItem( index ) );
		return null;
	}
	
	Icon GetFocusedItem()
	{
		return GetIcon( m_FocusedItemPosition );
	}
	
	override float GetFocusedContainerHeight( bool contents = false )
	{
		float x, y;
		if( GetFocusedItem() && contents )
			GetFocusedItem().GetRootWidget().GetScreenSize( x, y );
		else
			GetRootWidget().GetScreenSize( x, y );
		return y;
	}
	
	override float GetFocusedContainerYPos( bool contents = false )
	{
		float x, y;
		if( GetFocusedItem() && contents )
			GetFocusedItem().GetRootWidget().GetPos( x, y );
		else
			GetRootWidget().GetPos( x, y );
		return y;
	}
	
	override float GetFocusedContainerYScreenPos( bool contents = false )
	{
		float x, y;
		if( GetFocusedItem() && contents )
			GetFocusedItem().GetRootWidget().GetScreenPos( x, y );
		else
			GetRootWidget().GetScreenPos( x, y );
		return y;
	}
	
	void UpdateSelection()
	{
		if( m_IsActive )
		{
			if( m_FocusedItemPosition >= m_Icons.Count() )
				m_FocusedItemPosition = m_Icons.Count() - 1;
			Icon icon = GetIcon( m_FocusedItemPosition );
			if( icon )
			{
				icon.SetActive( true );
			}
		}
	}
	
	void UpdateRowVisibility( int count )
	{
		int i;
		int rows = Math.Max( 1, Math.Ceil( count / ROWS_NUMBER_XBOX ) );
		int diff = rows - m_Rows.Count();
		
		if( diff < 0 )
		{
			for( i = m_Rows.Count() - 1; i >= rows; i-- )
			{
				m_Rows.Remove( i );
			}
			m_Resizer2.ResizeParentToChild();
			m_Resizer1.ResizeParentToChild();
		}
		else if( diff > 0 )
		{
			m_MainWidget	= m_CargoContainer;
			for( i = m_Rows.Count(); i < rows; i++ )
			{
				ref CargoContainerRow row = new CargoContainerRow( this );
				
				row.SetNumber( i );
				row.SetEntity( m_Entity );
				row.GetRootWidget().SetSort( i );
				m_Rows.Insert( row );
			}
			m_MainWidget	= m_ItemsContainer;
			m_Resizer2.ResizeParentToChild();
			m_Resizer1.ResizeParentToChild();
		}
	}
	
	override void UpdateInterval()
	{
		if( m_Cargo )
		{
			int i;
			array<EntityAI> cargo_items = new array<EntityAI>;
			int prev_count = m_ShowedItemPositions.Count();
			
			//START - Add new item Icons
			for( i = 0; i < m_Cargo.GetItemCount(); i++ )
			{
				int x, y;
				m_Cargo.GetItemRowCol( i, y, x );
				EntityAI item = m_Cargo.GetItem( i );
				InventoryLocation il = new InventoryLocation;
				item.GetInventory().GetCurrentInventoryLocation( il );
				
				if( m_ShowedItemPositions.Contains( item ) )
				{
					ref Param3<ref Icon, int, int> data = m_ShowedItemPositions.Get( item );
					if( data.param1 )
					{
						if( data.param2 != x || data.param3 != y )
						{
							data.param2 = x;
							data.param3 = y;
							#ifdef PLATFORM_CONSOLE
								data.param1.SetCargoPos( data.param3 );
							#endif
							data.param1.SetPos( data.param2, data.param3 );
						}
						data.param1.UpdateInterval();
						cargo_items.Insert( item );
					}
				}
				else
				{
					ref Icon icon = new Icon( this );
					m_Icons.Insert( icon );
					InitIcon( icon, item, x, y );
					m_ShowedItemPositions.Insert( item, new Param3<ref Icon, int, int>( icon, x, y ) );
					cargo_items.Insert( item );
					UpdateHeaderText();
					#ifdef PLATFORM_CONSOLE
						UpdateSelection();
					#endif
				}
				
			}
			
			i = 0;
			while( i < m_ShowedItemPositions.Count() )
			{
				EntityAI item2	= m_ShowedItemPositions.GetKey( i );
				Icon ic			= m_ShowedItemPositions.GetElement( i ).param1;
				if( !item2 )
				{
					m_ShowedItemPositions.RemoveElement( i );
					if( ic )
						delete ic;
				}
				else 
				{
					if( cargo_items.Find( item2 ) == -1 )
					{
						m_Icons.RemoveItem( m_ShowedItemPositions.GetElement( i ).param1 );
						m_ShowedItemPositions.Remove( item2 );
						if( ic )
							delete ic;
						UpdateHeaderText();
						#ifdef PLATFORM_CONSOLE
							UpdateSelection();
						#endif
					}
					i++;
				}
			}
			
			#ifdef PLATFORM_CONSOLE
			if( prev_count != m_ShowedItemPositions.Count() )
			{
				UpdateRowVisibility( m_ShowedItemPositions.Count() );
				UpdateSelection();
			}
			#endif
		}
	}

	Icon InitIcon( Icon icon, EntityAI item, int pos_x, int pos_y )
	{
		#ifdef PLATFORM_CONSOLE
			icon.SetSize( 1, 1 );
			#ifdef PLATFORM_WINDOWS
				pos_y = pos_y * 5 + pos_x;
			#endif
			icon.SetCargoPos( pos_y );
			icon.SetPos( 0, pos_y );
		#else
			int size_x, size_y;
			GetGame().GetInventoryItemSize( InventoryItem.Cast( item ), size_x, size_y );
			icon.SetSize( size_x, size_y );
			icon.SetPos( pos_x, pos_y );
			icon.SetPosX( pos_x );
			icon.SetPosY( pos_y );
		#endif
		icon.Init( item );
		return icon;
	}
	
	override bool TransferItemToVicinity()
	{
		Man player = GetGame().GetPlayer();
		if( GetFocusedItem() )
		{
			EntityAI entity = EntityAI.Cast( GetFocusedItem().GetObject() );
			if( entity && player.CanDropEntity( entity ) )
			{
				player.PredictiveDropEntity( entity );
				return true;
			}
		}
		return false;
	}
	
	void SetDefaultFocus( bool while_micromanagment_mode = false )
	{
		if( !while_micromanagment_mode && ItemManager.GetInstance().IsMicromanagmentMode() )
		{
			return;
		}
		
		Unfocus();
		
		if( !IsEmpty() )
		{
			m_FocusedItemPosition = 0;
			UpdateSelection();
		}
		else
			m_FocusedItemPosition = 0;
	}
	
	void Unfocus()
	{
		if( GetFocusedItem() )
		{
			GetFocusedItem().SetActive( false );
		}
		m_FocusedItemPosition = 0;
	}
	
	override void UnfocusAll()
	{
		if( m_Icons )
		{
			foreach( Icon icon : m_Icons )
			{
				icon.SetActive( false );
			}
		}
		m_FocusedItemPosition = 0;
	}
	
	override EntityAI GetFocusedEntity()
	{
		Icon icon = GetFocusedItem();
		if( icon )
		{
			return EntityAI.Cast( icon.GetObject() );
		}
			
		return null;
	}
	
	override void SetLastActive()
	{
		if( GetFocusedItem() )
		{
			GetFocusedItem().SetActive( false );
		}
		m_FocusedItemPosition = ( ( m_Rows.Count() - 1 ) * ROWS_NUMBER_XBOX );
		UpdateSelection();
	}
	
	override void SetActive( bool active )
	{
		super.SetActive( active );
		if( active )
		{
			SetDefaultFocus();
		}
		else
		{
			UnfocusAll();
		}
	}
	
	override bool IsItemActive()
	{
		if( GetFocusedItem() )
		{
			ItemBase item = ItemBase.Cast( GetFocusedItem().GetObject() );
			return ( item != null );
		}
		return false;
	}
	
	override bool IsItemWithQuantityActive()
	{
		if( GetFocusedItem()  )
		{
			ItemBase item = ItemBase.Cast( GetFocusedItem().GetObject() );
			return ( !IsEmpty() && QuantityConversions.HasItemQuantity( item ) && item.CanBeSplit() );
		}
		return false;
	}
	
	override bool IsEmpty()
	{
		return m_Icons.Count() == 0;
	}
	
	int GetRecipeCount( bool recipe_anywhere, ItemBase entity1, ItemBase entity2, PlayerBase player )
	{
		PluginRecipesManager recipes_manager = PluginRecipesManager.Cast( GetPlugin( PluginRecipesManager ) );
		return recipes_manager.GetValidRecipes( entity1, entity2, null, player ) );
	}
	
	override bool CanEquip()
	{
		if( GetFocusedItem() )
		{
			EntityAI entity = EntityAI.Cast( GetFocusedItem().GetObject() );
			InventoryLocation il = new InventoryLocation;
			if( !entity.IsInherited( Magazine ) )
			{
				return GetGame().GetPlayer().GetInventory().FindFreeLocationFor( entity, FindInventoryLocationType.ATTACHMENT, il );
			}
		}
		return false;
	}
	
	override bool CanCombine()
	{
		if( GetFocusedItem() )
		{
			ItemBase entity			= ItemBase.Cast( GetFocusedItem().GetObject() );
			ItemBase item_in_hands	= ItemBase.Cast( GetGame().GetPlayer().GetHumanInventory().GetEntityInHands() );
			
			return ( ItemManager.GetCombinationFlags( entity, item_in_hands ) != 0 );
		}
		return false;
	}
	
	override bool CanCombineAmmo()
	{
		if( GetFocusedItem() )
		{
			ActionManagerClient amc	= ActionManagerClient.Cast( PlayerBase.Cast( GetGame().GetPlayer() ).GetActionManager() );
			
			ItemBase entity			= ItemBase.Cast( GetFocusedItem().GetObject() );
			ItemBase item_in_hands	= ItemBase.Cast( GetGame().GetPlayer().GetHumanInventory().GetEntityInHands() );
			
			return ( amc.CanPerformActionFromInventory( item_in_hands, entity ) || amc.CanSetActionFromInventory( item_in_hands, entity ) );
		}
		return false;
	}
	
	override bool TransferItem()
	{
		if( GetFocusedItem() )
		{
			EntityAI entity = EntityAI.Cast( GetFocusedItem().GetObject() );
			if( entity )
			{
				GetGame().GetPlayer().PredictiveTakeEntityToInventory( FindInventoryLocationType.CARGO, entity );
				return true;
			}
		}
		return false;
	}
	
	override bool EquipItem()
	{
		if( GetFocusedItem() )
		{
			ItemBase entity = ItemBase.Cast( GetFocusedItem().GetObject() );
			if( entity )
			{
				if( entity.HasQuantity() )
				{
					entity.OnRightClick();
					Icon icon = m_ShowedItemPositions.Get( entity ).param1;
					
					if ( icon )
					{
						icon.SetQuantity();
					}
				}
				else
				{
					GetGame().GetPlayer().PredictiveTakeEntityToInventory( FindInventoryLocationType.ATTACHMENT, entity );
					return true;
				}
			}
		}
		return false;
	}
	
	override bool SelectItem()
	{
		Icon focused_item = GetFocusedItem();
		if( focused_item )
		{
			ItemManager.GetInstance().SetSelectedItem( ItemBase.Cast( focused_item.GetObject() ), this, null );
			return true;
		}
		return false;
	}

	override bool Select()
	{
		EntityAI prev_item;
		if( GetFocusedItem() )
		{
			prev_item = EntityAI.Cast( GetFocusedEntity() );
		}
		Man player = GetGame().GetPlayer();
		
		if( ItemManager.GetInstance().IsItemMoving() )
		{
			EntityAI selected_item = ItemManager.GetInstance().GetSelectedItem();
			if( selected_item && m_Entity )
			{
				bool can_add = m_Entity.GetInventory().CanAddEntityInCargo( selected_item );
				bool in_cargo = !player.GetInventory().HasEntityInInventory( selected_item ) || !m_Entity.GetInventory().HasEntityInCargo( selected_item );
				if( can_add && in_cargo )
				{
					player.PredictiveTakeEntityToTargetCargo( m_Entity, selected_item );
					Container selected_cont2 = ItemManager.GetInstance().GetSelectedContainer();
					if( selected_cont2 )
					{
						selected_cont2.SetActive( false );
					}
					
					SetActive( true );
					m_FocusedItemPosition = 0;
					return true;
				}
				else
				{
					Container selected_cont = ItemManager.GetInstance().GetSelectedContainer();
					if( selected_cont )
					{
						selected_cont.SetActive( false );
					}
					
					SetActive( true );
					SetDefaultFocus( true );
				}
			}
		}
		else if ( prev_item && prev_item.GetInventory().CanRemoveEntity() )
		{
			EntityAI item_in_hands = GetGame().GetPlayer().GetHumanInventory().GetEntityInHands();
			if( item_in_hands )
			{
				if( GameInventory.CanSwapEntities( item_in_hands, prev_item ) )
				{
					player.PredictiveSwapEntities( item_in_hands, prev_item );
					return true;
				}
			}
			else
			{
				if( player.GetHumanInventory().CanAddEntityInHands( prev_item ) )
				{
					player.PredictiveTakeEntityToHands( prev_item );
					return true;
				}
			}
		}
		return false;
	}
	
	override bool Combine()
	{
		if( GetFocusedItem() )
		{
			Icon icon = GetFocusedItem();
			if( icon )
			{
				EntityAI item_in_hands	= GetGame().GetPlayer().GetHumanInventory().GetEntityInHands();
				EntityAI prev_item		= EntityAI.Cast( icon.GetObject() );
				if( item_in_hands && prev_item )
				{
					return icon.CombineItems( item_in_hands, prev_item );
				}
			}
		}
		return true;
	}
	
	override void MoveGridCursor( int direction )
	{
		if( !ItemManager.GetInstance().IsMicromanagmentMode() )
		{
			Container cnt;
			Icon icon = GetIcon( m_FocusedItemPosition );
			if( icon != null )
			{
				icon.SetActive( false );
				ItemManager.GetInstance().HideTooltip( );
			}
			
			int focused_row = m_FocusedItemPosition / ROWS_NUMBER_XBOX;
			int max_rows = m_Rows.Count() / 2 + 1;
			int row_min = focused_row * ROWS_NUMBER_XBOX;
			int row_max = row_min + ROWS_NUMBER_XBOX - 1;
			
			if(row_max >= m_Icons.Count() )
			{
				row_max = m_Icons.Count() - 1;
			}
			
			if( direction == Direction.UP )
			{
				m_FocusedItemPosition -= ROWS_NUMBER_XBOX;
				if( m_FocusedItemPosition < 0 )
				{
					m_FocusedItemPosition = m_Icons.Count() - 1;
					cnt = Container.Cast( GetParent() );
					if( cnt )
					{
						cnt.SetPreviousActive();
					}
					return;
				}
			}
			else if( direction == Direction.DOWN )
			{
				m_FocusedItemPosition += ROWS_NUMBER_XBOX;
				if( m_FocusedItemPosition > m_Icons.Count() - 1 )
				{
					if( focused_row < max_rows - 1 )
					{
						m_FocusedItemPosition = m_Icons.Count() - 1;
					}
					else
					{
						cnt = Container.Cast( GetParent() );
						if( cnt )
						{
							cnt.SetNextActive();
						}
						m_FocusedItemPosition = 0;
						return;
					}
				}
			}
			else if( direction == Direction.RIGHT )
			{
				m_FocusedItemPosition++;
				if( m_FocusedItemPosition > row_max  )
				{
					m_FocusedItemPosition = row_min;
				}
			}
			else if( direction == Direction.LEFT )
			{
				m_FocusedItemPosition--;
				if( m_FocusedItemPosition < row_min  )
				{
					m_FocusedItemPosition = row_max;
				}
			}
			
			icon = GetIcon( m_FocusedItemPosition );
			if( icon )
			{
				icon.SetActive( true );
			}
		}
		else
		{
			if( direction == Direction.UP )
			{
				cnt = Container.Cast( GetParent() );
				if( cnt )
				{
					cnt.SetPreviousActive();
				}
				m_FocusedItemPosition = 0;
				return;
			}
			else if( direction == Direction.DOWN )
			{
				cnt = Container.Cast( GetParent() );
				if( cnt )
				{
					cnt.SetNextActive();
				}
				m_FocusedItemPosition = 0;
				return;
			}
		}
	}
}