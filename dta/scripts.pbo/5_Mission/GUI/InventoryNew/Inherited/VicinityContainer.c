class VicinityContainer: CollapsibleContainer
{
	ref VicinitySlotsContainer			m_VicinityIconsContainer;
	ref map<EntityAI, ref Container>	m_ShowedItems				= new ref map<EntityAI, ref Container>;
	ref map<int, ref Container>			m_ShowedItemsIDs			= new ref map<int, ref Container>;
	ref array<EntityAI>					m_ShowedItemIcons			= new array<EntityAI>;
	
	const float DISTANCE_TO_ENTITIES 	= 1.0;
	const float DISTANCE_TO_THE_REST 	= 0.5;
	
	void VicinityContainer( LayoutHolder parent, int sort = -1 )
	{
		m_VicinityIconsContainer = new VicinitySlotsContainer( this );
		m_Body.Insert( m_VicinityIconsContainer );
		
		m_MainWidget = m_RootWidget.FindAnyWidget( "body" );
		WidgetEventHandler.GetInstance().RegisterOnChildAdd( m_MainWidget, this, "OnChildAdd" );
		WidgetEventHandler.GetInstance().RegisterOnChildRemove( m_MainWidget, this, "OnChildRemove" );
		
		RecomputeOpenedContainers();
		m_CollapsibleHeader.SetName("#container_vicinity");
		LoadDefaultState();
	}
	
	bool IsVicinityContainerIconsActive()
	{
		return m_VicinityIconsContainer.IsActive();
	}
	
	VicinitySlotsContainer GetVicinityIconsContainer()
	{
		return m_VicinityIconsContainer;
	}
	
	override void RefreshItemPosition( EntityAI item_to_refresh )
	{
		for ( int i = 0; i < m_ShowedItems.Count(); i++ )
		{
			Container container = m_ShowedItems.GetElement( i );
			container.RefreshItemPosition( item_to_refresh );
		}
	}
	
	override void RefreshQuantity( EntityAI item_to_refresh )
	{
		for ( int i = 0; i < m_ShowedItems.Count(); i++)
		{
			m_ShowedItems.GetElement( i ).RefreshQuantity( item_to_refresh );
		}
	}
	
	bool IsContainerWithCargoActive()
	{
		return ( ContainerWithCargo.Cast( GetFocusedContainer() ) != null );
	}
	
	bool IsItemWithAttachmentsActive()
	{
		return ( ContainerWithCargoAndAttachments.Cast( GetFocusedContainer() ) != null );
	}
	
	bool IsItemWithCategoriesActive()
	{
		return ( AttachmentCategoriesContainer.Cast( GetFocusedContainer() ) != null );
	}

	override void MoveGridCursor( int direction )
	{
		if( !GetFocusedContainer() || !GetFocusedContainer().IsActive() )
		{
			return;
		}
		
		ContainerWithCargo iwc = ContainerWithCargo.Cast( GetFocusedContainer() );
		ContainerWithCargoAndAttachments iwca = ContainerWithCargoAndAttachments.Cast( GetFocusedContainer() );
		ZombieContainer zmbc = ZombieContainer.Cast( GetFocusedContainer() );
		PlayerContainer plc = PlayerContainer.Cast( GetFocusedContainer() );
		if( iwc )
		{
			iwc.MoveGridCursor(direction);
		}
		else if ( iwca )
		{
			iwca.MoveGridCursor( direction );
		}
		else if ( iwca )
		{
			zmbc.MoveGridCursor( direction );
		}
		else if ( iwca )
		{
			plc.MoveGridCursor( direction );
		}
		else if( GetFocusedContainer() == m_VicinityIconsContainer )
		{
			m_VicinityIconsContainer.MoveGridCursor( direction );
		}
	}

	void TraverseShowedItems()
	{
		map<string, bool> serialized_types = new map<string, bool>();
		for ( int i = 0; i < m_ShowedItems.Count(); i++ )
		{
			EntityAI entity = m_ShowedItems.GetKey( i );
			Container container = m_ShowedItems.GetElement( i );
			string type = entity.GetType();
			if( container.IsInherited( ContainerWithCargo ) )
			{
				if( !serialized_types.Contains( type ) )
				{
					ContainerWithCargo item_with_cargo = ContainerWithCargo.Cast( container );
					serialized_types.Insert( type, item_with_cargo.IsOpened() );
				}
			}
		}

		if( serialized_types.Count() > 0 )
		{
			FileSerializer file = new FileSerializer();
			if ( file.Open( "inventory_state.save", FileMode.APPEND ) )
			{
				file.Write( serialized_types.Count() );

				for ( i = 0; i < serialized_types.Count(); i++ )
				{
					file.Write( serialized_types.GetKey( i ) );
					file.Write( serialized_types.GetElement( i ) );
				}
			}
			file.Close();
		}
	}

	override void DraggingOverHeader( Widget w, int x, int y, Widget receiver )
	{
		if( w == null )
		{
			return;
		}
		
		ItemPreviewWidget ipw = ItemPreviewWidget.Cast( w.FindAnyWidget( "Render" ) );
		if( !ipw )
		{
			string name = w.GetName();
			name.Replace( "PanelWidget", "Render" );
			ipw = ItemPreviewWidget.Cast( w.FindAnyWidget( name ) );
		}
		
		if( !ipw && ItemPreviewWidget.Cast( w ) )
		{
			ipw = ItemPreviewWidget.Cast( w );
		}

		if( !ipw || !ipw.GetItem() )
		{
			return;
		}

		if( ipw.GetItem() && GetGame().GetPlayer().CanDropEntity( ipw.GetItem() ) && ipw.GetItem().GetInventory().CanRemoveEntity() && m_ShowedItemIcons.Find( ipw.GetItem() ) == -1 )
		{
			ColorManager.GetInstance().SetColor( w, ColorManager.GREEN_COLOR );
			ItemManager.GetInstance().HideDropzones();
			ItemManager.GetInstance().GetLeftDropzone().SetAlpha( 1 );
		}
		else
		{
			ColorManager.GetInstance().SetColor( w, ColorManager.RED_COLOR );
			ItemManager.GetInstance().ShowSourceDropzone( ipw.GetItem() );
		}
	}

	void DraggingOverIcon( Widget w, int x, int y, Widget receiver )
	{
		string name = receiver.GetName();
		name.Replace("PanelWidget", "Render");
		ItemPreviewWidget receiver_iw = ItemPreviewWidget.Cast( receiver.FindAnyWidget(name) );
		EntityAI receiver_item = receiver_iw.GetItem();

		ItemPreviewWidget ipw = ItemPreviewWidget.Cast( w.FindAnyWidget( "Render" ) );
		if( !ipw )
		{
			name = w.GetName();
			name.Replace( "PanelWidget", "Render" );
			ipw = ItemPreviewWidget.Cast( w.FindAnyWidget( name ) );
		}
		
		if( !ipw && ItemPreviewWidget.Cast( w ) )
		{
			ipw = ItemPreviewWidget.Cast( w );
		}
		else
		{
			return;
		}

		if( !ItemBase.Cast( receiver_item ) || !ipw.GetItem() )
		{
			return;
		}

		if( ipw.GetItem().GetInventory().CanRemoveEntity() || m_ShowedItemIcons.Find( ipw.GetItem() ) > -1 )
		{
			if ( ( ItemBase.Cast( receiver_item ) ).CanBeCombined( ItemBase.Cast( ipw.GetItem() ) ) )
			{
				ColorManager.GetInstance().SetColor( w, ColorManager.COMBINE_COLOR );
				ItemManager.GetInstance().HideDropzones();
				ItemManager.GetInstance().GetLeftDropzone().SetAlpha( 1 );
				return;
			}
			else if( GameInventory.CanSwapEntities( receiver_item, ipw.GetItem() ) )
			{
				ColorManager.GetInstance().SetColor( w, ColorManager.SWAP_COLOR );
				ItemManager.GetInstance().HideDropzones();
				ItemManager.GetInstance().GetLeftDropzone().SetAlpha( 1 );
				return;
			}
			else if( GetGame().GetPlayer().CanDropEntity( ipw.GetItem() ) )
			{
				ColorManager.GetInstance().SetColor( w, ColorManager.GREEN_COLOR );
				ItemManager.GetInstance().HideDropzones();
				ItemManager.GetInstance().GetLeftDropzone().SetAlpha( 1 );
				return;
			}
		}
			
		ColorManager.GetInstance().SetColor( w, ColorManager.RED_COLOR );
		ItemManager.GetInstance().ShowSourceDropzone( ipw.GetItem() );
	}

	void OnDropReceivedFromIcon( Widget w, int x, int y, Widget receiver )
	{
		string name = receiver.GetName();
		name.Replace("PanelWidget", "Render");
		ItemPreviewWidget receiver_iw = ItemPreviewWidget.Cast( receiver.FindAnyWidget(name) );
		EntityAI receiver_item = receiver_iw.GetItem();

		ItemPreviewWidget ipw = ItemPreviewWidget.Cast( w.FindAnyWidget( "Render" ) );
		if( !ipw )
		{
			name = w.GetName();
			name.Replace( "PanelWidget", "Render" );
			ipw = ItemPreviewWidget.Cast( w.FindAnyWidget( name ) );
		}
		
		if( !ipw && ItemPreviewWidget.Cast( w ) )
		{
			ipw = ItemPreviewWidget.Cast( w );
		}
		else
		{
			return;
		}

		if( !ItemBase.Cast( receiver_item ) || !ipw.GetItem() )
		{
			return;
		}
		
		EntityAI item = ipw.GetItem();
		bool equal_typed = item.GetType() == receiver_item.GetType();
		if( !receiver_item.IsInherited( ItemBase ) || item == null || !equal_typed )
		{
			return;
		}
		
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );

		if( !item.GetInventory().CanRemoveEntity() || m_ShowedItemIcons.Find( item ) > -1 )
			return;
		
		if ( ( ItemBase.Cast( receiver_item ) ).CanBeCombined( ItemBase.Cast( item ) ) )
		{
			( ItemBase.Cast( receiver_item ) ).CombineItemsClient( ItemBase.Cast( item ) );
		}
		else if( GameInventory.CanSwapEntities( receiver_item, item ) )
		{
			if( !receiver_item.GetInventory().CanRemoveEntity() )
				return;
			player.PredictiveSwapEntities( item, receiver_item );
		}
		else if( player.CanDropEntity( item ) )
		{
			player.PredictiveDropEntity( item );
		}
		
		ItemManager.GetInstance().SetIsDragging( false );
		ItemManager.GetInstance().PrepareTooltip( item );

		InventoryMenu menu = InventoryMenu.Cast( GetGame().GetUIManager().FindMenu( MENU_INVENTORY ) );
		if ( menu )
		{
			menu.RefreshQuickbar();
		}
	}
	
	override void SetNextActive()
	{
		super.SetNextActive();
		if( m_ActiveIndex == 1 )
			m_CollapsibleHeader.SetActive( true );
		else
			m_CollapsibleHeader.SetActive( false );
	}
	
	override void SetPreviousActive( bool force = false )
	{
		super.SetPreviousActive( force );
		if( m_ActiveIndex == 1 )
			m_CollapsibleHeader.SetActive( true );
		else
			m_CollapsibleHeader.SetActive( false );
	}
	
	void OnLeftPanelDropReceived( Widget w, int x, int y, Widget receiver )
	{
		OnDropReceivedFromHeader( w, x, y, receiver );
	}

	override void OnDropReceivedFromHeader( Widget w, int x, int y, Widget receiver )
	{
		if( !w )
			return;
		
		ItemPreviewWidget ipw = ItemPreviewWidget.Cast( w.FindAnyWidget( "Render" ) );
		
		if( !ipw )
		{
			string name = w.GetName();
			name.Replace( "PanelWidget", "Render" );
			ipw = ItemPreviewWidget.Cast( w.FindAnyWidget( name ) );
		}
		
		if( !ipw )
		{
			ipw = ItemPreviewWidget.Cast( w );
		}
		if( !ipw )
			return;
		
		EntityAI item = ipw.GetItem();
		if( !ipw.IsInherited( ItemPreviewWidget ) || !item )
		{
			return;
		}
		
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		
		if( !item.GetInventory().CanRemoveEntity() || m_ShowedItemIcons.Find( item ) > -1 )
			return;
		
		if( player.CanDropEntity( item ) )
		{
			ItemBase item_base = ItemBase.Cast( item );
			if( item_base )
			{
				float stackable = item_base.ConfigGetFloat("varStackMax");
				if( stackable == 0 || item_base.GetQuantity() <= stackable )
				{
					player.PredictiveDropEntity( item );
				}
				else if( stackable != 0 && stackable <= item_base.GetQuantity() )
				{
					item_base.SplitIntoStackMaxClient( null, -1 );
				}
			}
		}

		InventoryMenu menu = InventoryMenu.Cast( GetGame().GetUIManager().FindMenu( MENU_INVENTORY ) );
		if ( menu )
		{
			menu.RefreshQuickbar();
		}
	}

	void OnDropReceivedFromEmptySpace( Widget w, int x, int y, Widget receiver )
	{
		OnDropReceivedFromHeader( w, x, y, receiver );
	}

	override void UpdateInterval()
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		
		if(!player)
			return;
		
		EntityAI eai;
		vector pos = player.GetPosition();
		ref array<EntityAI> objects = new array<EntityAI>;
		ref array<Object> objects_in_radius = new array<Object>;
		ref array<Object> objects_in_radius_up = new array<Object>;
		ref array<Object> objects_in_cone = new array<Object>;
		ref array<CargoBase> proxyCargos = new array<CargoBase>;
		
		GetGame().GetObjectsAtPosition3D( pos, GameInventory.c_MaxItemDistanceRadius, objects_in_radius, proxyCargos );
		objects_in_radius.RemoveItem( player );
		
		objects_in_cone = ActionTargets.GetVicinityObjects();
		
		for ( int i = 0; i < objects_in_radius.Count(); i++ )
		{
			eai = EntityAI.Cast( objects_in_radius.Get( i ) );
			if( eai )
			{
				float distance = vector.Distance( pos, eai.GetPosition() );
				if ( eai != player && !eai.IsInherited( Particle ) )
				{				
					if ( eai.IsInherited( PlayerBase ) || eai.IsInherited( ZombieBase ) )
					{
						if ( distance <= DISTANCE_TO_ENTITIES )
						{
							objects.Insert( eai );
						}
					}
					else
					{
						if ( distance <= DISTANCE_TO_THE_REST )
						{
							objects.Insert( eai );
						}
					}
				}
			}
		}
		
		//Create another check sphere 0.5m above the first one
		pos[1] = pos[1] + 0.5;
		GetGame().GetObjectsAtPosition3D( pos, GameInventory.c_MaxItemDistanceRadius, objects_in_radius_up, proxyCargos );
		objects_in_radius_up.RemoveItem( player );
		
		for ( int j = 0; j < objects_in_radius_up.Count(); j++ )
		{
			eai = EntityAI.Cast( objects_in_radius_up.Get( j ) );
			if( eai )
			{
				float distance_up = vector.Distance( pos, eai.GetPosition() );
				if ( !eai.IsInherited( Particle ) )
				{				
					if ( !eai.IsInherited( PlayerBase ) || !eai.IsInherited( ZombieBase ) )
					{
						if ( distance_up <= DISTANCE_TO_THE_REST )
						{
							if ( eai && objects.Find( eai ) == INDEX_NOT_FOUND )
							{
								objects.Insert( eai );
							}
						}
					}
				}
			}
		}
		
		for ( int k = 0; k < objects_in_cone.Count(); k++ )
		{
			eai = EntityAI.Cast( objects_in_cone.Get( k ) );
			if( eai )
			{
				if( objects.Find( eai ) == INDEX_NOT_FOUND && GameInventory.CheckManipulatedObjectsDistances( eai, player, GameInventory.c_MaxItemDistanceRadius ) )
					objects.Insert( eai );
			}
		}

		//GetItemsShowableInInventory
		array<EntityAI> showable_items = new array<EntityAI>;
		int m_OldShowedItemIconsCount = m_ShowedItemIcons.Count();
		m_ShowedItemIcons.Clear();
		
		for( i = 0; i < objects.Count(); i++ )
		{
			eai = objects.Get( i );
			bool showable_item = eai.IsInventoryVisible();
			
			if ( player.GetInventory().IsPlaceholderEntity( eai ) )
				continue; // noproxy: ignore body placeholder

			if( showable_item )
			{
				showable_items.Insert( eai );

				if( !eai.IsInherited( DayZInfected ) && !eai.IsInherited( PlayerBase ) )
				{
					m_ShowedItemIcons.Insert( eai );
				}
			}
		}

		ref map<EntityAI, ref Container> new_showed_items = new ref map<EntityAI, ref Container>;
		ref map<int, ref Container> showed_items_IDs = new ref map<int, ref Container>;
		for ( i = 0; i < showable_items.Count(); i++ )
		{
			EntityAI entity = showable_items.Get( i );
			if( entity )
			{
				if( !m_ShowedItems.Contains( entity ) && entity.GetInventory() )
				{
					string config = "CfgVehicles " + entity.GetType() + " GUIInventoryAttachmentsProps";

					if( GetGame().ConfigIsExisting( config ) )
					{
						AttachmentCategoriesContainer ac = new AttachmentCategoriesContainer( m_Parent, -1 );
						ac.SetEntity( entity );
						new_showed_items.Insert( entity, ac );
						showed_items_IDs.Insert( entity.GetID(), ac);
					}
					else if ( entity.GetSlotsCountCorrect() > 0 && entity.GetInventory().GetCargo() )
					{
						if( entity.IsInherited( DayZInfected ) )
						{
							if( entity.IsAlive() )
							{
								continue;
							}
							ZombieContainer zmb_cnt = new ZombieContainer( m_Parent, -1 );
							zmb_cnt.SetEntity( entity );
							new_showed_items.Insert( entity, zmb_cnt );
							showed_items_IDs.Insert( entity.GetID(), zmb_cnt );
							Container.Cast( GetParent() ).Insert( zmb_cnt );
						}
						else
						{
							ContainerWithCargoAndAttachments iwca = new ContainerWithCargoAndAttachments( this, -1 );
							iwca.SetEntity( entity );
							new_showed_items.Insert( entity, iwca );
							showed_items_IDs.Insert( entity.GetID(), iwca );
						}
					}
					else if( entity.GetInventory().GetCargo() )
					{
						ContainerWithCargo iwc = new ContainerWithCargo( this, -1 );
						iwc.SetEntity( entity );
						new_showed_items.Insert( entity, iwc );
						showed_items_IDs.Insert( entity.GetID(), iwc );
						iwc.UpdateInterval();
					}
					else if( entity.GetSlotsCountCorrect() > 0 )
					{
						if( entity.HasEnergyManager() )
						{
							ContainerWithElectricManager iwem = new ContainerWithElectricManager( this, -1 );
							iwem.SetEntity( entity );
							new_showed_items.Insert( entity, iwem );
							showed_items_IDs.Insert( entity.GetID(), iwem );
						}
						else
						{
							if ( entity.IsInherited( PlayerBase ) )
							{
								if( entity.IsAlive() && ( !PlayerBase.Cast( entity ).IsUnconscious() && !PlayerBase.Cast( entity ).IsRestrained() ) )
								{
									continue;
								}
								
								PlayerContainer plyr_cnt = new PlayerContainer( m_Parent );
								plyr_cnt.SetPlayer( PlayerBase.Cast( entity ) );
								Container.Cast( GetParent() ).Insert( plyr_cnt );
								( Container.Cast( m_Parent ) ).Refresh();
								new_showed_items.Insert( entity, plyr_cnt );
								showed_items_IDs.Insert( entity.GetID(), plyr_cnt);
							}
							else
							{
								ContainerWithCargoAndAttachments iwcas = new ContainerWithCargoAndAttachments( this, -1 );
								iwcas.SetEntity( entity );
								new_showed_items.Insert( entity, iwcas );
								showed_items_IDs.Insert( entity.GetID(), iwcas );
							}
						}
					}
				}
				else
				{
					if( m_ShowedItems.Get( entity ) )
					{
						if ( entity.IsInherited( PlayerBase ) )
						{
							if( entity.IsAlive() && ( !PlayerBase.Cast( entity ).IsUnconscious() && !PlayerBase.Cast( entity ).IsRestrained() ) )
							{
								continue;
							}
						}
						new_showed_items.Insert( entity, m_ShowedItems.Get( entity ) );
						showed_items_IDs.Insert( entity.GetID(), m_ShowedItemsIDs.Get( entity.GetID() ) );
					}
				}
			}
		}

//			Print(m_ShowedItems.Count());
		
		for ( i = 0; i < m_ShowedItems.Count(); i++ )
		{
			EntityAI ent = m_ShowedItems.GetKey( i );
			m_ShowedItems.GetElement( i ).UpdateInterval();
			if( !new_showed_items.Contains( ent ) )
			{
				Container con = m_ShowedItems.GetElement( i );
				GetMainWidget().Update();
				Container.Cast( GetParent() ).Remove( con );
				Remove( con );
			}
		}
		
		m_ShowedItems = new_showed_items;
		m_ShowedItemsIDs = showed_items_IDs;
		RecomputeOpenedContainers();
		UpdateCollapseButtons();
		m_VicinityIconsContainer.ShowItemsInContainers( m_ShowedItemIcons );
		
		if( m_ShowedItemIcons.Count() < m_OldShowedItemIconsCount )
		{
			Inventory in = Inventory.Cast( GetRoot() );
			if( in )
				in.UpdateConsoleToolbar();	
		}
	}

	void ToggleContainer( Container conta )
	{
		Container cont = conta;
		ClosableContainer c;
		if( cont )
		{
			if( cont.IsInherited( ClosableContainer ) )
			{
				c = ClosableContainer.Cast( cont );
				if( c.IsOpened() )
				{
					c.Close();
				}
				else
				{
					c.Open();
				}
			}
			else if( cont.IsInherited( VicinitySlotsContainer ) )
			{
				VicinitySlotsContainer c2 = VicinitySlotsContainer.Cast( cont );
				if( m_VicinityIconsContainer == c2 )
				{
					EntityAI e = c2.GetActiveItem();
					c = ClosableContainer.Cast( m_ShowedItems.Get( e ) );
					if( c )
					{
						if( c.IsOpened() )
						{
							c.Close();
						}
						else
						{
							c.Open();
						}
					}
				}
			}
			else if( cont.IsInherited( CollapsibleContainer ) )
			{
				CollapsibleContainer c3 = CollapsibleContainer.Cast( cont );
				c3.CollapseButtonOnMouseButtonDown( null );
			}
		}
	}
	
	void ExpandCollapseContainer()
	{
		ToggleContainer( GetFocusedContainer() );
	}
	
	override bool OnChildRemove( Widget w, Widget child )
	{
		w.Update();
		float x, y;
		w.GetScreenSize( x, y );
		if( w == GetMainWidget() )
		{
			GetMainWidget().Update();
			m_Parent.OnChildRemove( w, child );
		}
		return true;
	}
	
	override bool OnChildAdd( Widget w, Widget child )
	{
		if( w == GetMainWidget() )
		{
			GetMainWidget().Update();
			m_Parent.OnChildAdd( w, child );
		}
		return true;
	}

	override void CollapseButtonOnMouseButtonDown(Widget w)
	{
		super.CollapseButtonOnMouseButtonDown(w);
		ItemManager.GetInstance().SetDefaultHeaderOpenState( "VICINITY", !m_Hidden );
	}
}
