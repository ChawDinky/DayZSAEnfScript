class HandsContainer: Container
{
	ref HandsHeader m_CollapsibleHeader;
	protected bool m_Hidden;
	protected ref Attachments m_Atts;
	protected ref UICargoGrid m_Cargo;
	EntityAI m_am_entity1, m_am_entity2;
	ref IconsContainer m_IconsContainer;

	void HandsContainer( LayoutHolder parent )
	{
		m_CollapsibleHeader = new HandsHeader( this, "CollapseButtonOnMouseButtonDown" );

		m_Body = new array<ref LayoutHolder>;
		HandsPreview hands_preview = new HandsPreview( this );
		ItemManager.GetInstance().SetHandsPreview( hands_preview );
		m_Body.Insert( hands_preview );

		GetMainWidget().SetFlags( WidgetFlags.IGNOREPOINTER );
		LoadDefaultState();
	}
	
	Widget GetLastRowWidget()
	{
		return m_Cargo.GetLastRowWidget();
	}
	
	override void SetNextActive()
	{
		if( m_Cargo )
		{
			if( !m_Cargo.IsActive() )
			{
				SetActive( false );
				m_Cargo.SetActive( true );
			}
			else
			{
				SetActive( true );
				m_Cargo.SetActive( false );
			}
		}
		else if( m_Atts )
		{
			if( !m_Atts.IsActive() )
			{
				SetActive( false );
				m_Atts.SetActive( true );
			}
			else
			{
				SetActive( true );
				m_Atts.SetActive( false );
			}
		}
	}
	
	override void SetPreviousActive()
	{
		if( m_Cargo )
		{
		
			if( !m_Cargo.IsActive() )
			{
				SetActive( false );
				m_Cargo.SetActive( true );
			}
			else
			{
				SetActive( true );
				m_Cargo.SetActive( false );
			}
		}
		else if( m_Atts )
		{
			if( !m_Atts.IsActive() )
			{
				SetActive( false );
				m_Atts.SetActive( true );
			}
			else
			{
				SetActive( true );
				m_Atts.SetActive( false );
			}
		}
	}

	void MouseClick2( Widget w, int x, int y, int button )
	{
		string name = w.GetName();
		name.Replace( "PanelWidget", "Render" );
		ItemPreviewWidget item_preview = ItemPreviewWidget.Cast( w.FindAnyWidget( name ) );
		
		if( !item_preview )
		{
			return;
		}
		
		EntityAI item = item_preview.GetItem();
		InventoryItem itemAtPos = InventoryItem.Cast( item );
		
		if( item )
		{
			if ( button == MouseState.MIDDLE )
			{
				InspectItem( itemAtPos );
			}
		}
	}
		
	void DraggingOverHeader2(Widget w, int x, int y, Widget receiver )
	{
		DraggingOverHeader(w, x, y, receiver );
	}
	
	override void TransferItem()
	{
		if( m_Cargo && m_Cargo.IsActive() )
		{
			m_Cargo.TransferItem();
		}
		else if( m_Atts && m_Atts.IsActive() )
		{
			m_Atts.TransferItem();
		}
		else
		{
			EntityAI item_in_hands = GetGame().GetPlayer().GetHumanInventory().GetEntityInHands();
			if( item_in_hands && GetGame().GetPlayer().GetHumanInventory().CanRemoveEntityInHands() )
			{
				if( GetGame().GetPlayer().PredictiveTakeEntityToInventory( FindInventoryLocationType.CARGO, item_in_hands ) )
				{
					m_MainWidget.FindAnyWidget("Selected").Show( false );
					m_MainWidget.FindAnyWidget("hands_preview_root").SetAlpha( 1 );
				}
			}
		}
	}
	
	bool CanEquip()
	{
		EntityAI item_in_hands = GetGame().GetPlayer().GetHumanInventory().GetEntityInHands();
		if( item_in_hands.IsInherited( Magazine ) )
		{
			return false;
		}
		InventoryLocation il = new InventoryLocation;
		bool found = GetGame().GetPlayer().GetInventory().FindFreeLocationFor(item_in_hands,FindInventoryLocationType.ATTACHMENT,il);
		if (found)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	override void EquipItem()
	{
		if( m_Cargo && m_Cargo.IsActive() )
		{
			m_Cargo.EquipItem();
		}
		else if( m_Atts && m_Atts.IsActive() )
		{
			m_Atts.EquipItem();
		}
		else
		{
			ItemBase item_in_hands = ItemBase.Cast( GetGame().GetPlayer().GetHumanInventory().GetEntityInHands() );
			if( item_in_hands && !item_in_hands.IsInherited( Magazine )  )
			{
				if( item_in_hands.CanBeSplit() )
				{
					item_in_hands.OnRightClick();
				}
				if( GetGame().GetPlayer().GetHumanInventory().CanRemoveEntityInHands() )
				{
					if( GetGame().GetPlayer().PredictiveTakeEntityToInventory( FindInventoryLocationType.ATTACHMENT, item_in_hands ) )
					{
						m_MainWidget.FindAnyWidget("Selected").Show( false );
						m_MainWidget.FindAnyWidget("hands_preview_root").SetAlpha( 1 );
					}
				}
			}
		}
	}
	
	override void SetActive( bool active )
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		EntityAI item_in_hands = player.GetHumanInventory().GetEntityInHands();
		if( item_in_hands )
		{
			if( !m_MainWidget.FindAnyWidget("Selected") )
			{
				return;
			}
			m_MainWidget.FindAnyWidget("Selected").Show(active);
			if( active == false )
			{
				if( m_Cargo )
				{
					m_Cargo.SetActive( active );
				}
				else if( m_Atts )
				{
					m_Atts.SetActive( active );
				}
			}
			if( active )
			{
				float x, y;
				GetMainWidget().GetScreenPos( x, y );
				ItemManager.GetInstance().PrepareTooltip( item_in_hands, x, y );
			}
		}
		else
		{
			m_MainWidget.FindAnyWidget("hands_preview_root").SetAlpha(active);
		}
	}
	
	override bool IsActive()
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		EntityAI item_in_hands = player.GetHumanInventory().GetEntityInHands();
		if( item_in_hands )
		{
			if( m_Cargo )
			{
				return m_MainWidget.FindAnyWidget("Selected").IsVisible() || m_Cargo.IsActive();
			}
			else if( m_Atts )
			{
				return m_MainWidget.FindAnyWidget("Selected").IsVisible() || m_Atts.IsActive();
			}
			else
			{
				if( m_MainWidget.FindAnyWidget("Selected") )
				{
					return m_MainWidget.FindAnyWidget("Selected").IsVisible();
				}
				else
				{
					return m_MainWidget.FindAnyWidget("hands_preview_root").GetAlpha();		
				}
			}
		}
		else
		{
			return m_MainWidget.FindAnyWidget("hands_preview_root").GetAlpha();
		}
		return false;
	}
	
	bool IsItemActive()
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		ItemBase item = ItemBase.Cast( player.GetHumanInventory().GetEntityInHands() );
		if( item == NULL )
		{
			return false;
		}
		return !IsEmpty() && ( !QuantityConversions.HasItemQuantity( item )  || ( QuantityConversions.HasItemQuantity( item ) && !item.CanBeSplit() ) );
	}
	
	bool IsItemWithQuantityActive()
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		ItemBase item = ItemBase.Cast( player.GetHumanInventory().GetEntityInHands() );
		if( item == NULL )
		{
			return false;
		}
		return !IsEmpty() && QuantityConversions.HasItemQuantity( item ) && item.CanBeSplit();
	}
	
	bool IsEmpty()
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		return player.GetHumanInventory().GetEntityInHands() == NULL;
	}
	
	void TransferItemToVicinity()
	{
		if( m_Cargo && m_Cargo.IsActive() )
		{
			m_Cargo.TransferItemToVicinity();
		}
		else if( m_Atts && m_Atts.IsActive() )
		{
			m_Atts.TransferItemToVicinity();
		}
		else
		{
			PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
			EntityAI item_in_hands = player.GetHumanInventory().GetEntityInHands();
			if( item_in_hands && player.CanDropEntity( item_in_hands ) && GetGame().GetPlayer().GetHumanInventory().CanRemoveEntityInHands() )
			{
				if( player.PredictiveDropEntity( item_in_hands ) )
				{
					m_MainWidget.FindAnyWidget("Selected").Show( false );
					m_MainWidget.FindAnyWidget("hands_preview_root").SetAlpha(1);;
				}
			}
		}
	}

	/*override void Select()
	{
		if( m_Cargo )
		{
			m_Cargo.Select();
		}
	}*/
	
	override void SelectItem()
	{
		Man player = GetGame().GetPlayer();
		EntityAI item_in_hands = player.GetHumanInventory().GetEntityInHands();
		ItemManager.GetInstance().SetSelectedItem( item_in_hands, NULL, NULL );
	}
	
	bool to_reselect;
	EntityAI item_to_be_swap;
	EntityAI prev_item;
	override void Select()
	{
		Man player = GetGame().GetPlayer();
		EntityAI item_in_hands = player.GetHumanInventory().GetEntityInHands();
		if( ItemManager.GetInstance().IsMicromanagmentMode() )
		{
			EntityAI selected_item = ItemManager.GetInstance().GetSelectedItem();
			if( selected_item && selected_item.GetInventory().CanRemoveEntity() )
			{
				if( item_in_hands && item_in_hands.GetInventory().CanRemoveEntity() )
				{
					if( GameInventory.CanSwapEntities( item_in_hands, selected_item ) )
					{
						player.PredictiveSwapEntities( item_in_hands, selected_item );
						to_reselect = true;
						item_to_be_swap = selected_item;
					}
				}
				else
				{
					if( player.GetHumanInventory().CanAddEntityInHands( selected_item ) )
					{
		 				ItemBase item_base = ItemBase.Cast( selected_item );
						float stackable = item_base.ConfigGetFloat("varStackMax");
						if( stackable == 0 || item_base.GetQuantity() <= stackable )
						{
							GetGame().GetPlayer().PredictiveTakeEntityToHands( item_base );		
						}
						else if( stackable != 0 && stackable <= item_base.GetQuantity() )
						{
							item_base.SplitIntoStackMaxHandsClient( PlayerBase.Cast( GetGame().GetPlayer() ) );
						}
						
						Widget selected_widget = ItemManager.GetInstance().GetSelectedWidget();
						if( selected_widget )
						{
							selected_widget.Show( false );
						}
						to_reselect = true;
					}
					return;
				}
			}
		}
		else if( m_Cargo && m_Cargo.GetFocusedItem() )
		{
			prev_item = EntityAI.Cast( m_Cargo.GetFocusedItem().GetObject() );
			if ( prev_item && prev_item.GetInventory().CanRemoveEntity() )
			{
				if( item_in_hands )
				{
					if( GameInventory.CanSwapEntities( item_in_hands, prev_item ) )
					{
						player.PredictiveSwapEntities( item_in_hands, prev_item );
					}
				}
				else
				{
					if( player.GetHumanInventory().CanAddEntityInHands( prev_item ) )
					{
						player.PredictiveTakeEntityToHands( prev_item );
					}
				}
				m_Cargo.PrepareCursorReactivation();
			}
		}
		else if( m_Atts && m_Atts.GetFocusedEntity() )
		{
			prev_item = m_Atts.GetFocusedEntity();
			if ( prev_item && prev_item.GetInventory().CanRemoveEntity() )
			{
				if( item_in_hands )
				{
					if( GameInventory.CanSwapEntities( item_in_hands, prev_item ) )
					{
						player.PredictiveSwapEntities( item_in_hands, prev_item );
					}
				}
				else
				{
					if( player.GetHumanInventory().CanAddEntityInHands( prev_item ) )
					{
						player.PredictiveTakeEntityToHands( prev_item );
					}
				}
			}
		}
	}
	
	EntityAI GetItemPreviewItem( Widget w )
	{
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
		{
			return null;
		}
		
		return ipw.GetItem();
	}

	override void DraggingOverHeader( Widget w, int x, int y, Widget receiver )
	{
		if( w == NULL )
		{
			return;
		}
		string name = w.GetName();
		name.Replace( "PanelWidget", "Render" );

		ItemPreviewWidget w_ipw = ItemPreviewWidget.Cast( w.FindAnyWidget( name ) );
		if( w_ipw == NULL )
		{
			w_ipw = ItemPreviewWidget.Cast( w.FindAnyWidget( "Render" ) );
		}
		if( w_ipw == NULL )
		{
			return;
		}

		PlayerBase p = PlayerBase.Cast( GetGame().GetPlayer() );
		InventoryItem receiver_entity = InventoryItem.Cast( p.GetHumanInventory().GetEntityInHands() );
		InventoryItem w_entity = InventoryItem.Cast( w_ipw.GetItem() );
		if( !w_entity )
		{
			return;
		}

		if( receiver_entity != NULL && GameInventory.CanSwapEntities( receiver_entity, w_entity ) )
		{
			ColorManager.GetInstance().SetColor( w, ColorManager.SWAP_COLOR );
			ItemManager.GetInstance().HideDropzones();
			ItemManager.GetInstance().GetRootWidget().FindAnyWidget( "HandsPanel" ).FindAnyWidget( "DropzoneX" ).SetAlpha( 1 );
		}
		else
		{
			//if( m_HandsIcon )
			{
				ColorManager.GetInstance().SetColor( w, ColorManager.SWAP_COLOR );
				ItemManager.GetInstance().HideDropzones();
				ItemManager.GetInstance().GetRootWidget().FindAnyWidget( "HandsPanel" ).FindAnyWidget( "DropzoneX" ).SetAlpha( 1 );
			}
			/*else
			{
				ColorManager.GetInstance().SetColor( w, ColorManager.RED_COLOR );
				ItemManager.GetInstance().ShowSourceDropzone( w_entity );
			}*/
		}
	}

	void OnDropReceivedFromHeader2( Widget w, int x, int y, Widget receiver )
	{
		ItemPreviewWidget ipw = ItemPreviewWidget.Cast( w.FindAnyWidget( "Render" ) );
		PlayerBase p = PlayerBase.Cast( GetGame().GetPlayer() );
		EntityAI item = p.GetHumanInventory().GetEntityInHands();

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

		if( !ipw.IsInherited( ItemPreviewWidget ) )
		{
			return;
		}

		if( !ipw.GetItem() )
		{
			return;
		}

		EntityAI receiver_item;
		name = receiver.GetName();
		name.Replace("PanelWidget", "Render");
		ItemPreviewWidget receiver_iw = ItemPreviewWidget.Cast( receiver.FindAnyWidget(name) );
		if( receiver_iw )
			receiver_item = receiver_iw.GetItem();

		if( !item.GetInventory().CanRemoveEntity() )
			return;
		
		Weapon_Base wpn;
		Magazine mag;
		if ( Class.CastTo(wpn,  item ) && Class.CastTo(mag,  ipw.GetItem() ) )
		{
			if( p.GetWeaponManager().CanAttachMagazine( wpn, mag ) )
			{
				p.GetWeaponManager().AttachMagazine( mag );
			}
		}
		else if (receiver_item)
		{
			if ( ( ItemBase.Cast( receiver_item ) ).CanBeCombined( ItemBase.Cast( ipw.GetItem() ) ) )
			{
				( ItemBase.Cast( receiver_item ) ).CombineItemsClient( ItemBase.Cast( ipw.GetItem() ) );
			}
			else if( GameInventory.CanSwapEntities( receiver_item, ipw.GetItem() ) )
			{
				if( !receiver_item.GetInventory().CanRemoveEntity() )
					return;
				GetGame().GetPlayer().PredictiveSwapEntities( ipw.GetItem(), receiver_item );
			}
		}
		else if( item.GetInventory().CanAddAttachment( ipw.GetItem() ) )
		{
			p.PredictiveTakeEntityToTargetAttachment( item, ipw.GetItem() );
		}

	}
/*	void InjectValidRecipes( EntityAI entity1, EntityAI entity2,ContextMenu cmenu, bool recipes_anywhere = false )
	{
		PlayerBase p = GetGame().GetPlayer();
		array<int> recipes_ids = p.m_Recipes;
		PluginRecipesManager plugin_recipes_manager = GetPlugin( PluginRecipesManager );
		plugin_recipes_manager.GetValidRecipes( entity1,entity2,recipes_ids, p );

		for( int x = 0;x < recipes_ids.Count();x++ )
		{
			int id = recipes_ids.Get( x );
			string name = plugin_recipes_manager.GetRecipeName( id );

			cmenu.Add( name, this, "OnPerformRecipe",new Param1<int>( id ) );
		}
	}*/

	void OnIconDrag( Widget w )
	{
		ItemManager.GetInstance().SetIsDragging( true );
		string name = w.GetName();
		name.Replace( "PanelWidget", "Render" );
		ItemPreviewWidget ipw = ItemPreviewWidget.Cast( w.FindAnyWidget(name) );
		float icon_x, icon_y, x_content, y_content;
		int m_sizeX, m_sizeY;

		InventoryItem i_item = InventoryItem.Cast( ipw.GetItem() );
		GetGame().GetInventoryItemSize( i_item, m_sizeX, m_sizeY );

		m_Parent.m_Parent.GetMainWidget().FindAnyWidget( "body" ).GetScreenSize( x_content, y_content );
		icon_x = x_content / 10;
		icon_y = x_content / 10;
		w.SetFlags( WidgetFlags.EXACTSIZE );
		w.SetSize( icon_x, icon_y );
		w.SetSize( icon_x * m_sizeX - 1 , icon_y * m_sizeY + m_sizeY - 1 );

		if( !ipw.GetItem() )
		{
			return;
		}
		name.Replace( "Render", "Col" );
		w.FindAnyWidget( name ).Show( true );
		name.Replace( "Col", "Temperature" );
		w.FindAnyWidget( name ).Show( false );
	}

	void OnIconDrop( Widget w )
	{
		ItemManager.GetInstance().HideDropzones();

		ItemManager.GetInstance().SetIsDragging( false );
		w.ClearFlags( WidgetFlags.EXACTSIZE );
		w.SetSize( 1, 1 );
		string name = w.GetName();
		name.Replace( "PanelWidget", "Col" );
		w.FindAnyWidget( name ).Show( false );
		name.Replace( "Col", "Temperature" );
		w.FindAnyWidget( name ).Show( false );
		name.Replace( "Temperature", "GhostSlot" );
		w.GetParent().FindAnyWidget( name ).Show( true );
		name.Replace( "GhostSlot", "Render" );
		ItemPreviewWidget ipw = ItemPreviewWidget.Cast( w.FindAnyWidget(name) );
	}

	void OnPerformCombination(int combinationFlags)
	{
		PlayerBase m_player = PlayerBase.Cast( GetGame().GetPlayer() );
		if ( m_am_entity1 == NULL || m_am_entity2 == NULL ) return;

		if ( combinationFlags == InventoryCombinationFlags.NONE ) return;

		if ( combinationFlags & InventoryCombinationFlags.LOAD_CHAMBER )
		{
			Magazine mag;
			if ( Class.CastTo(mag,  m_am_entity2 ) )
			{
				m_player.GetWeaponManager().LoadBullet( mag );
				return;
			}
		}

		if ( combinationFlags & InventoryCombinationFlags.ADD_AS_ATTACHMENT )
		{
			if( m_Atts )
			{
				m_Atts.Remove();
				delete m_Atts;
			}
			if( m_am_entity2.GetSlotsCountCorrect() > 0 )
			{
				m_Atts = new Attachments( this, m_am_entity2 );
				m_Atts.InitAttachmentGrid( 1 );

			}

			this.Refresh();
			m_Parent.Refresh();

			Weapon_Base wpn1;
			Magazine mag1;
			if ( Class.CastTo(wpn1,  m_am_entity1 ) && Class.CastTo(mag1,  m_am_entity2 ) )
			{
				if( m_player.GetWeaponManager().CanAttachMagazine(wpn1, mag1) )
				{
					m_player.GetWeaponManager().AttachMagazine(mag1);
					return;
				}
			}
			m_player.PredictiveTakeEntityToTargetAttachment( m_am_entity1, m_am_entity2 );
		}

		if ( combinationFlags & InventoryCombinationFlags.ADD_AS_CARGO )
		{
			m_player.PredictiveTakeEntityToTargetCargo( m_am_entity1, m_am_entity2 );
		}

		if ( combinationFlags & InventoryCombinationFlags.SWAP )
		{
			Magazine swapmag1;
			Magazine swapmag2;
			if (Class.CastTo(swapmag1,  m_am_entity1 ) && Class.CastTo(swapmag2,  m_am_entity2 ) )
			{
				if( m_player.GetWeaponManager().CanSwapMagazine( Weapon_Base.Cast( swapmag1.GetParent() ), Magazine.Cast( swapmag2 ) ) )
				{
					m_player.GetWeaponManager().SwapMagazine(swapmag2);
					return;
				}

				if( m_player.GetWeaponManager().CanSwapMagazine(Weapon_Base.Cast( swapmag2.GetParent() ), Magazine.Cast( swapmag1 )) )
				{
					m_player.GetWeaponManager().SwapMagazine(swapmag1);
					return;
				}
			}
			if( !m_player.PredictiveSwapEntities( m_am_entity1, m_am_entity2 ) && m_player.GetHumanInventory().CanAddEntityInHands( m_am_entity1 ) )
			{
				m_player.PredictiveTakeEntityToHands( m_am_entity1 );
			}
//			GetDragGrid().GetContainer().HideExpandView(m_am_entity2);
		}

		if ( combinationFlags & InventoryCombinationFlags.TAKE_TO_HANDS )
		{
			if( m_Atts )
			{
				m_Atts.Remove();
				delete m_Atts;
			}

			if( m_am_entity2.GetSlotsCountCorrect() > 0 )
			{
				m_Atts = new Attachments( this, m_am_entity2 );
				m_Atts.InitAttachmentGrid( 1 );

			}
			this.Refresh();
			m_Parent.Refresh();
			
			if( m_player.GetHumanInventory().CanAddEntityInHands( m_am_entity2 ) )
			{
				m_player.PredictiveTakeEntityToHands( m_am_entity2 );
			}
		}
		/*
		if (m_am_entity1.IsInherited(ItemBase) && m_am_entity2.IsInherited(ItemBase))
		{
			ItemBase entity1ItemBase = m_am_entity1;
			if (combinationFlags & InventoryCombinationFlags.COMBINE_QUANTITY)
			{
				entity1ItemBase.QuantityCombine(m_am_entity2);
			}
		}*/
	}

	void ShowActionMenuCombine( EntityAI entity1, EntityAI entity2, int combinationFlags )
	{
		if ( entity1 && entity2 ) PrintString( "Showing action menu for " + entity1.GetDisplayName() + " and " + entity2.GetDisplayName() );

		ContextMenu cmenu = GetGame().GetUIManager().GetMenu().GetContextMenu();
		m_am_entity1 = entity1;
		m_am_entity2 = entity2;
		cmenu.Hide();
		cmenu.Clear();

		/*if( combinationFlags & InventoryCombinationFlags.RECIPE_HANDS )
		{
			GetGame().ProfilerStart( "RECIPES_PROFILER" );

			InjectValidRecipes( entity1, entity2, cmenu, false );

			GetGame().ProfilerStop( "RECIPES_PROFILER" );
		}
		else if( combinationFlags & InventoryCombinationFlags.RECIPE_ANYWHERE )
		{
			InjectValidRecipes( entity1, entity2, cmenu, true );
		}*/

		if( combinationFlags & InventoryCombinationFlags.COMBINE_QUANTITY2 )
		{
			ItemBase entity = ItemBase.Cast( entity1 );
			entity.CombineItemsClient( ItemBase.Cast( entity2 ) );
			return;
		}

		if ( entity1 == NULL || entity2 == NULL ) return;

		if ( combinationFlags == InventoryCombinationFlags.NONE ) return;

		if ( combinationFlags & InventoryCombinationFlags.ADD_AS_ATTACHMENT )
		{
			cmenu.Add( "#inv_context_add_as_attachment", this, "OnPerformCombination", new Param1<int>( InventoryCombinationFlags.ADD_AS_ATTACHMENT ) );
		}
		if ( combinationFlags & InventoryCombinationFlags.LOAD_CHAMBER )
		{
			cmenu.Add( "#inv_context_load_chamber", this, "OnPerformCombination", new Param1<int>( InventoryCombinationFlags.LOAD_CHAMBER ) );
		}

		if ( combinationFlags & InventoryCombinationFlags.ADD_AS_CARGO )
		{
			cmenu.Add( "#inv_context_add_as_cargo", this, "OnPerformCombination", new Param1<int>( InventoryCombinationFlags.ADD_AS_CARGO ) );
		}

		if ( combinationFlags & InventoryCombinationFlags.SWAP )
		{
			cmenu.Add( "#inv_context_swap", this, "OnPerformCombination", new Param1<int>( InventoryCombinationFlags.SWAP ) );
		}

		if ( combinationFlags & InventoryCombinationFlags.TAKE_TO_HANDS )
		{
			cmenu.Add( "#inv_context_take_to_hands", this, "OnPerformCombination", new Param1<int>( InventoryCombinationFlags.TAKE_TO_HANDS ) );
		}

		if ( combinationFlags & InventoryCombinationFlags.COMBINE_QUANTITY )
		{
			cmenu.Add( "#inv_context_combine", this, "OnPerformCombination", new Param1<int>( InventoryCombinationFlags.COMBINE_QUANTITY ) );
		}

		int m_am_pos_x,  m_am_pos_y;
		GetMousePos( m_am_pos_x, m_am_pos_y );
		m_am_pos_x -= 5;
		m_am_pos_y -= 5;

		cmenu.Show( m_am_pos_x, m_am_pos_y );
	}

	override bool OnDrag( Widget w, int x, int y )
	{
		ItemManager.GetInstance().SetIsDragging( true );
		string name = w.GetName();
		name.Replace( "PanelWidget", "Render" );
		ItemPreviewWidget ipw = ItemPreviewWidget.Cast( w.FindAnyWidget( name ) );

		float icon_x, icon_y, x_content, y_content;
		int m_sizeX, m_sizeY;

		InventoryItem i_item = InventoryItem.Cast( ipw.GetItem() );
		GetGame().GetInventoryItemSize( i_item, m_sizeX, m_sizeY );

		m_Parent.m_Parent.GetMainWidget().FindAnyWidget( "body" ).GetScreenSize( x_content, y_content );
		icon_x = x_content / 10;
		icon_y = x_content / 10;
		w.SetFlags( WidgetFlags.EXACTSIZE );
		w.SetSize( icon_x, icon_y );
		w.SetSize( icon_x * m_sizeX - 1 , icon_y * m_sizeY + m_sizeY - 1 );

		if( !ipw.GetItem() )
		{
			return false;
		}

		name.Replace( "Render", "Col" );
		w.FindAnyWidget( name ).Show( true );
		ItemManager.GetInstance().SetDraggedItem( ipw.GetItem() );

		return false;
	}

	override bool OnDrop( Widget w, int x, int y, Widget reciever )
	{
		ItemManager.GetInstance().SetIsDragging( false );
		w.ClearFlags( WidgetFlags.EXACTSIZE );
		w.SetSize( 1, 1 );
		string name = w.GetName();
		name.Replace( "PanelWidget", "Col" );
		w.FindAnyWidget( name ).Show( false );
		name.Replace( "Col", "Render" );
		ItemPreviewWidget ipw = ItemPreviewWidget.Cast( w.FindAnyWidget( name ) );
		ipw.SetItem( NULL );
		ItemManager.GetInstance().SetDraggedItem( NULL );

		return false;
	}

	override void OnDropReceivedFromHeader( Widget w, int x, int y, Widget receiver )
	{
		//HandsPreview preview = m_Body.Get( 0 );
		//preview.DropReceived( w, x, y, receiver );
		string name = w.GetName();
		name.Replace( "PanelWidget", "Render" );

		ItemPreviewWidget receiver_ipw = ItemPreviewWidget.Cast( receiver.FindAnyWidget( "Render" ) );
		/*if( m_HandsIcon )
		{
			receiver_ipw = receiver.GetParent().FindAnyWidget( "Render" );
		}*/

		ItemPreviewWidget w_ipw = ItemPreviewWidget.Cast( w.FindAnyWidget( name ) );
		if( w_ipw == NULL )
		{
			w_ipw = ItemPreviewWidget.Cast( w.FindAnyWidget( "Render" ) );
		}
		if( w_ipw == NULL )
		{
			return;
		}

		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		EntityAI item_in_hands = player.GetHumanInventory().GetEntityInHands();
		InventoryItem receiver_entity = InventoryItem.Cast( item_in_hands );
		InventoryItem w_entity = InventoryItem.Cast( w_ipw.GetItem() );
		if( !w_entity )
		{
			return;
		}

		Weapon_Base wpn;
		Magazine mag;

		if ( Class.CastTo(wpn,  item_in_hands ) && Class.CastTo(mag,  w_entity ) && Class.CastTo(wpn,  mag.GetHierarchyParent() ) )
		{
			return;
		}

		if( receiver_entity != NULL && GameInventory.CanSwapEntities( receiver_entity, w_entity ) )
		{
			GetGame().GetPlayer().PredictiveSwapEntities( w_entity, receiver_entity );

			Icon icon = ItemManager.GetInstance().GetDraggedIcon();
			if( m_Parent.IsInherited( IconsContainer ) )
			{
				//m_Timers[0].Run(0.1, this, "ToRefresh",  new Param2<Icon, Icon>(this, icon), true);
			}
		}
		else
		{
				InventoryLocation inv_loc_src = new InventoryLocation;
				InventoryLocation inv_loc_dst = new InventoryLocation;
				if( item_in_hands )
				{
					item_in_hands.GetInventory().GetCurrentInventoryLocation( inv_loc_src );
					player.GetInventory().FindFreeLocationFor( item_in_hands, FindInventoryLocationType.ANY, inv_loc_dst );

					// todle je nejaky divny ne?
					//TryMoveEntity( inv_loc_src, inv_loc_dst );
					if( inv_loc_dst.IsValid() && player.GetHumanInventory().CanAddEntityInHands( w_entity ) )
					{
						player.PredictiveTakeEntityToHands( w_entity );
					}
				}
				else
				{
					if( player.GetHumanInventory().CanAddEntityInHands( w_entity ) )
					{
						player.PredictiveTakeEntityToHands( w_entity );
					}
				}
		}
	}

	override void RefreshQuantity( EntityAI item_to_refresh )
	{
		HandsPreview preview = HandsPreview.Cast( m_Body.Get( 0 ) );
		preview.RefreshQuantity( item_to_refresh );
	}

	int GetCombinationFlags( EntityAI entity1, EntityAI entity2 )
	{
		int flags = 0;
		PlayerBase m_player = PlayerBase.Cast( GetGame().GetPlayer() );
		EntityAI entity_in_hands = m_player.GetHumanInventory().GetEntityInHands();

		if ( !entity1 || !entity2 ) return flags;

		Magazine swapmag1;
		Magazine swapmag2;
		bool skipSwap = false;

		if( Class.CastTo(swapmag1, entity1) && Class.CastTo(swapmag2, entity2) )
		{
			Weapon_Base parentWpn;

			if(	Class.CastTo(parentWpn, swapmag1.GetHierarchyParent())	)
			{
				skipSwap = true;
				if( m_player.GetWeaponManager().CanSwapMagazine(parentWpn,swapmag2) )
					flags = flags | InventoryCombinationFlags.SWAP;
			}

			if(	Class.CastTo(parentWpn, swapmag2.GetHierarchyParent())	)
			{
				skipSwap = true;
				if( m_player.GetWeaponManager().CanSwapMagazine(parentWpn,swapmag1) )
					flags = flags | InventoryCombinationFlags.SWAP;

			}
		}

		if ( !skipSwap )
		{
			if ( entity1 == m_player.GetHumanInventory().GetEntityInHands() ) flags = flags | InventoryCombinationFlags.TAKE_TO_HANDS;
			else if ( GameInventory.CanSwapEntities( entity1, entity2 ) )
			{
				if ( !entity1.IsInherited( ZombieBase ) && !entity1.IsInherited( Car ) )
				{
					flags = flags | InventoryCombinationFlags.SWAP;
				}
			}
		}

		if ( entity1.IsInherited( ItemBase) && entity2.IsInherited( ItemBase ) )
		{
			ItemBase ent1 = ItemBase.Cast( entity1 );
			if ( ent1.CanBeCombined( ItemBase.Cast( entity2 ), PlayerBase.Cast( m_player ) ) ) flags = flags | InventoryCombinationFlags.COMBINE_QUANTITY2;
		}

		Weapon_Base wpn;
		Magazine mag;
		if ( Class.CastTo(wpn,  entity1 ) && Class.CastTo(mag,  entity2 ) )
		{
			int muzzleIndex = wpn.GetCurrentMuzzle();
			if ( m_player.GetWeaponManager().CanLoadBullet(wpn, mag) )
			{
				flags = flags | InventoryCombinationFlags.LOAD_CHAMBER;
			}
			else if ( m_player.GetWeaponManager().CanAttachMagazine(wpn, mag) )
			{
				flags = flags | InventoryCombinationFlags.ATTACH_MAGAZINE;
			}
		}
		else if ( entity1.GetInventory().CanAddAttachment( entity2 ) )
		{
			if ( !entity1.IsInherited( ZombieBase ) && !entity1.IsInherited( Car ) && !entity2.IsInherited( ZombieBase ) && !entity2.IsInherited( Car ) )
			{
				flags = flags | InventoryCombinationFlags.ADD_AS_ATTACHMENT;
			}
		}
		if ( entity1.GetInventory().CanAddEntityInCargo( entity2 ) ) flags = flags | InventoryCombinationFlags.ADD_AS_CARGO;

		if( entity1 == m_player.GetHumanInventory().GetEntityInHands() || entity2 == m_player.GetHumanInventory().GetEntityInHands() )
		{
		//Debug.Log("GetCombinationFlags called, setting comb. flag","recipes");
			if( GetRecipeCount( false, entity1, entity2 ) > 0 )
			{
				flags = flags | InventoryCombinationFlags.RECIPE_HANDS;
			}

			ActionManagerClient amc;
			Class.CastTo(amc, m_player.GetActionManager());
			if( entity1 == m_player.GetHumanInventory().GetEntityInHands() )
			{
				if( amc.CanSetActionFromInventory( ItemBase.Cast( entity1 ), ItemBase.Cast( entity2 ) ) )
				{
					flags = flags | InventoryCombinationFlags.SET_ACTION;
				}
			}
			else
			{
				if( amc.CanSetActionFromInventory( ItemBase.Cast( entity2 ), ItemBase.Cast( entity1 ) ) )
				{
					flags = flags | InventoryCombinationFlags.SET_ACTION;
				}
			}
		}

		if( GetRecipeCount( true, entity1, entity2 ) > 0 )
		{
			flags = flags | InventoryCombinationFlags.RECIPE_ANYWHERE;
		}
		return flags;
	}

	int GetRecipeCount( bool recipe_anywhere, EntityAI entity1, EntityAI entity2 )
	{
		PluginRecipesManager plugin_recipes_manager = PluginRecipesManager.Cast( GetPlugin( PluginRecipesManager ) );
		return plugin_recipes_manager.GetValidRecipes( ItemBase.Cast( entity1 ), ItemBase.Cast( entity2 ), NULL, PlayerBase.Cast( GetGame().GetPlayer() ) );
	}
	
	void DestroyAtt()
	{
		if( m_Atts )
		{
			m_Atts.Remove();
			delete m_Atts;
		}

		this.Refresh();
		m_Parent.Refresh();
	}
	
	override void UnfocusGrid()
	{
		if( m_Cargo )
		{
			m_Cargo.Unfocus();
		}
		else if( m_Atts )
		{
			m_Atts.UnfocusAll();
		}
	}
	
	override void MoveGridCursor( int direction )
	{
		if( m_Cargo && m_Cargo.IsActive() )
		{
			m_Cargo.MoveGridCursor( direction );
		} else if ( m_Atts && m_Atts.IsActive() )
		{
			m_Atts.MoveGridCursor( direction );
		} else if( direction == Direction.UP )
		{
			SetPreviousActive();
		}
		else if( direction == Direction.DOWN )
		{
			SetNextActive();
		}
	}
	
	void DestroyCargo()
	{
		if( m_Cargo )
		{
			this.Remove(m_IconsContainer);
			m_Cargo.Remove();
			delete m_Cargo;
		}

		this.Refresh();
		m_Parent.Refresh();
	}
	
	void DropReceived( Widget w,  int x, int y )
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		EntityAI item_in_hands = player.GetHumanInventory().GetEntityInHands();
		
		EntityAI item = GetItemPreviewItem( w );
		if( !item )
		{
			return;
		}

		int idx = 0;
		int c_x, c_y;
		
		if( item_in_hands.GetInventory().GetCargo() )
		{
			c_x = item_in_hands.GetInventory().GetCargo().GetHeight();
			c_y = item_in_hands.GetInventory().GetCargo().GetWidth();
		}
		
		if( !item_in_hands.GetInventory().CanRemoveEntity() )
			return;
		
		if( c_x > x && c_y > y && item_in_hands.GetInventory().CanAddEntityInCargoEx( item, idx, x, y ) )
		{
			player.PredictiveTakeEntityToTargetCargoEx( item_in_hands, item, idx, x, y );

			Icon icon = m_IconsContainer.GetIcon( item.GetID() );
			
			if( icon )
			{
				w.FindAnyWidget("Color").SetColor( ColorManager.BASE_COLOR );
				icon.RefreshPos( x, y );
				icon.Refresh();
				Refresh();
			}
		}
	}
	
	bool DraggingOverGrid( Widget w,  int x, int y, Widget reciever )
	{
		EntityAI item_in_hands = GetGame().GetPlayer().GetHumanInventory().GetEntityInHands();
		if( w == NULL )
		{
			return false;
		}
		EntityAI item = GetItemPreviewItem( w );
		if( !item )
		{
			return false;
		}

		int color;
		int idx = 0;
		int c_x, c_y;
		
		if( item_in_hands.GetInventory().GetCargo() )
		{
			c_x = item_in_hands.GetInventory().GetCargo().GetHeight();
			c_y = item_in_hands.GetInventory().GetCargo().GetWidth();
		}
		
		if( c_x > x && c_y > y && item_in_hands.GetInventory().CanAddEntityInCargoEx( item, 0, x, y ) )
		{
			ItemManager.GetInstance().HideDropzones();
			/*if( item_in_hands.GetHierarchyParent() == GetGame().GetPlayer() )
			{
				ItemManager.GetInstance().GetRootWidget().FindAnyWidget( "RightPanel" ).FindAnyWidget( "DropzoneX" ).SetAlpha( 1 );
			}
			else
			{
				ItemManager.GetInstance().GetRootWidget().FindAnyWidget( "LeftPanel" ).FindAnyWidget( "DropzoneX" ).SetAlpha( 1 );
			}*/
			ItemManager.GetInstance().GetRootWidget().FindAnyWidget( "HandsPanel" ).FindAnyWidget( "DropzoneX" ).SetAlpha( 1 );
			color = ColorManager.GREEN_COLOR;
		}
		else
		{
			color = ColorManager.RED_COLOR;
			ItemManager.GetInstance().ShowSourceDropzone( item );
		}

		if( w.FindAnyWidget("Color") )
		{
			w.FindAnyWidget("Color").SetColor( color );
		}
		else
		{
			string name = w.GetName();
			name.Replace( "PanelWidget", "Col" );
			w.FindAnyWidget( name ).SetColor( color );
		}

		return true;
	}

	void ShowAtt( EntityAI entity )
	{
		if( entity.GetSlotsCountCorrect() > 0 )
		{
			m_Atts = new Attachments( this, entity );
			m_Atts.InitAttachmentGrid( 1 );
		}
		
		if( entity.GetInventory().GetCargo() )
		{
			m_IconsContainer = new IconsContainer( this );
			this.Insert( m_IconsContainer );
			m_Cargo = new UICargoGrid( entity, m_IconsContainer );
			m_Cargo.SetParent( this );
		}

		if( entity.GetInventory().IsInventoryLockedForLockType( HIDE_INV_FROM_SCRIPT ) )
		{
			HideContent();
		}
		else
		{
			ShowContent();
		}

		this.Refresh();
		m_Parent.Refresh();
	}
	
	void RefreshHands()
	{
		for ( int i = 1; i < m_Body.Count(); i++ )
		{
			m_Body.Get( i ).OnShow();
		}
		this.Refresh();
		m_Parent.Refresh();
	}
	
	void Reselect()
	{
		EntityAI item_in_hands = GetGame().GetPlayer().GetHumanInventory().GetEntityInHands();
		if( item_to_be_swap == NULL || item_to_be_swap == item_in_hands)
		{
			if( to_reselect )
			{
				if( item_in_hands )
				{
					m_MainWidget.FindAnyWidget("Selected").Show( true );
					m_MainWidget.FindAnyWidget("hands_preview_root").SetAlpha( 0 );
					to_reselect = false;
				}
			}
		}
	}

	override void UpdateInterval()
	{
		super.UpdateInterval();
		
		if( m_Atts )
		{
			m_Atts.RefreshAtt();
		}
		if( m_Cargo )
		{
			m_Cargo.UpdateInterval();
		}
		
		ElectricityIcon();
		m_CollapsibleHeader.UpdateInterval();
	}

	override void SetLayoutName()
	{
		m_LayoutName = WidgetLayoutName.ClosableContainer;
	}

	override void OnShow()
	{
		super.OnShow();

		for ( int i = 0; i < m_Body.Count(); i++ )
		{
			m_Body.Get( i ).OnShow();
		}
	}

	void DoubleClick(Widget w, int x, int y, int button)
	{
		if( button == MouseState.LEFT )
		{
			if( w == NULL )
			{
				return;
			}
			ItemPreviewWidget iw = ItemPreviewWidget.Cast( w.FindAnyWidget( "Render" ) );
			if( !iw )
			{
			  string name = w.GetName();
			  name.Replace( "PanelWidget", "Render" );
			  iw = ItemPreviewWidget.Cast( w.FindAnyWidget( name ) );
			}
			if( !iw )
			{
			  iw = ItemPreviewWidget.Cast( w );
			}
			if( !iw.GetItem() )
			{
				return;
			}
	
			ItemBase item = ItemBase.Cast( iw.GetItem() );
			
			PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
			EntityAI item_in_hands = player.GetHumanInventory().GetEntityInHands();
			Weapon_Base wpn;
			Magazine mag;
			if( Class.CastTo(wpn, item_in_hands ) )
			{
				return;
			}
	
			if( !item.GetInventory().CanRemoveEntity() )
				return;
			
			if( player.GetInventory().HasEntityInInventory( item ) && player.GetHumanInventory().CanAddEntityInHands( item ) )
			{
				player.PredictiveTakeEntityToHands( item );
			}
			else
			{
				if( player.GetInventory().CanAddEntityToInventory( item ) && player.GetHumanInventory().CanRemoveEntityInHands() )
				{
					if( item.ConfigGetFloat("varStackMax") )
						item.SplitIntoStackMaxClient( player, -1, );
					else
						player.PredictiveTakeEntityToInventory( FindInventoryLocationType.ANY, InventoryItem.Cast( item ) );
				}
				else
				{
					if( player.GetHumanInventory().CanAddEntityInHands( item ) )
					{
						player.PredictiveTakeEntityToHands( item );
					}
				}
			}
	
			ItemManager.GetInstance().HideTooltip();
	
			name = w.GetName();
			name.Replace( "PanelWidget", "Temperature" );
			w.FindAnyWidget( name ).Show( false );
		}
	}
	
	int GetCargoHeight()
	{
		return m_Cargo.GetCargoHeight();
	}
	
	void ElectricityIcon()
	{
		EntityAI item_in_hands = GetGame().GetPlayer().GetHumanInventory().GetEntityInHands();
		if( item_in_hands && item_in_hands.GetCompEM() )
		{
			if( GetMainWidget().FindAnyWidget( "electricity" ) )
			{
				bool show_electricity_icon = item_in_hands.GetCompEM().HasElectricityIcon();
				GetMainWidget().FindAnyWidget( "electricity" ).Show( show_electricity_icon );
			}
			
			if( GetMainWidget().FindAnyWidget( "electricity_can_work" ) )
			{
				bool show_electricity_can_work_icon = item_in_hands.GetCompEM().CanWork() && !item_in_hands.IsRuined();
				GetMainWidget().FindAnyWidget( "electricity_can_work" ).Show( show_electricity_can_work_icon );
			}
		}
		else
		{
			GetMainWidget().FindAnyWidget( "electricity" ).Show( false );
		}
	}

	void LoadDefaultState()
	{
		//m_Hidden = !ItemManager.GetInstance().GetDefaultOpenStateHands( );

		if( m_Hidden )
		{
			for ( int i = 1; i < m_Body.Count(); i++ )
			{
				m_Body.Get( i ).OnHide();
			}
		}
		else
		{
			for ( i = 1; i < m_Body.Count(); i++ )
			{
				m_Body.Get( i ).OnShow();
			}
		}

		GetMainWidget().FindAnyWidget("opened").Show(!m_Hidden);
		GetMainWidget().FindAnyWidget("closed").Show(m_Hidden);
	}

	void CollapseButtonOnMouseButtonDown( Widget w )
	{
		if( !m_Hidden )
		{
			for ( int i = 1; i < m_Body.Count(); i++ )
			{
				m_Body.Get( i ).OnHide();
			}
			m_Hidden = true;
		}
		else
		{
			for ( i = 1; i < m_Body.Count(); i++ )
			{
				m_Body.Get( i ).OnShow();
			}
			m_Hidden = false;
		}

		w.FindAnyWidget("opened").Show(!m_Hidden);
		w.FindAnyWidget("closed").Show(m_Hidden);

		ItemManager.GetInstance().SetDefaultOpenStateHands( !m_Hidden );

		m_Parent.Refresh();
	}
}
