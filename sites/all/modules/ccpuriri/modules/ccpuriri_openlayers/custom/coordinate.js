(function($) {

	// declare a global object which is initialized by attach
	Drupal.ccpuriri = Drupal.ccpuriri || {};
	Drupal.ccpuriri.openlayers = Drupal.ccpuriri.openlayers || {};

	/**
	 * Attaches the openlayers behavior This will display a marker in the
	 * control, when map moves the coordinate is updated
	 */
	Drupal.behaviors.CCPURIRI_OPENLAYERS_COORDINATE = {
		attach : function(context, settings) {

			// get the container project
			var layers = Drupal.ccpuriri.openlayers.layers;

			var map = Drupal.ccpuriri.openlayers.layers.map;

			var mapCenter = map.getCenter();

			var myLocation = new OpenLayers.Geometry.Point(mapCenter.lon,
					mapCenter.lat);

			// The overlay layer for our marker, with a simple diamond as symbol
			layers.overlay = new OpenLayers.Layer.Vector(
					'Overlay',
					{
						styleMap : new OpenLayers.StyleMap(
								{
									externalGraphic : 'http://www.openlayers.org/dev/img/marker-gold.png',
									graphicWidth : 20,
									graphicHeight : 24,
									graphicYOffset : -24,
									title : '${tooltip}'
								})
					});

			// We add the marker with a tooltip text to the overlay
			layers.pointFeature = new OpenLayers.Feature.Vector(myLocation, {
				tooltip : 'OpenLayers'
			});

			layers.overlay.addFeatures([ layers.pointFeature ]);

			map.addLayer(layers.overlay);

			// A popup with some information about our location
			layers.popup = new OpenLayers.Popup.Anchored("Popup", mapCenter,
					new OpenLayers.Size(60, 60),
					'It is right here', // this can be any html
					null, true // <--
																			// true
																			// if
																			// we
																			// want
																			// a
																			// close
																			// (X)
																			// button,
																			// false
																			// otherwise
			);

			// and add the popup to it.
			map.addPopup(layers.popup);

			// register events

			map.events.register("move", null, function() {
				// update
				mapCenter = map.getCenter();

				mapCentralMoveTo(mapCenter);		
				// update form fields
				mapCenter.transform(layers.baseProjection,
						layers.defaultProjection);

				$('#ccpuriri_openlayers_lat').val(mapCenter.lat);
				$('#ccpuriri_openlayers_lon').val(mapCenter.lon);

			});
			
			$(Drupal.ccpuriri).on(
					Drupal.ccpuriri.AddressChangeEvent,
					function(event, loc){
						if(loc.lon && loc.lat && loc.lon!=0 && loc.lat !=0)
							{	
								// move map to
								layers.MapShow(loc.lon,loc.lat);
							}
							
						
					}
					
			);
			
			var mapCentralMoveTo = function (mapcenter) {
			
				// update point feature
				layers.pointFeature.move(mapcenter);
				// update popup
				layers.popup.lonlat = mapcenter;
				layers.popup.updatePosition();

			}
			
		}
	};

})(jQuery);