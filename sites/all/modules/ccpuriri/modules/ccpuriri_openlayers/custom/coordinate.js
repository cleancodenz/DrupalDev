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

			
		     /*
	           * Mark style
	           */
	        var style_mark = OpenLayers.Util.extend({}, OpenLayers.Feature.Vector.style['default']);
	        // each of the three lines below means the same, if only one of
	        // them is active: the image will have a size of 24px, and the
	        // aspect ratio will be kept
	        // style_mark.pointRadius = 12;
	        // style_mark.graphicHeight = 24; 
	        // style_mark.graphicWidth = 24;

	        // if graphicWidth and graphicHeight are both set, the aspect ratio
	        // of the image will be ignored
	        style_mark.graphicWidth = 24;
	        style_mark.graphicHeight = 20;
	        style_mark.graphicXOffset = 10; // default is -(style_mark.graphicWidth/2);
	        style_mark.graphicYOffset = -style_mark.graphicHeight;
	        style_mark.externalGraphic = 'http://www.openlayers.org/dev/img/marker.png';
	        // title only works in Firefox and Internet Explorer
	        style_mark.title = '${tooltip}';
	        
			/*
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
			*/
	    	layers.overlay = new OpenLayers.Layer.Vector('Overlay');
	    	
	        
			// We add the marker with a tooltip text to the overlay
			layers.pointFeature = new OpenLayers.Feature.Vector(myLocation, {
				tooltip : 'OpenLayers',
				style: style_mark,
			});

		//	layers.overlay.addFeatures([ layers.pointFeature ]);

	
			layers.circleFeature =new OpenLayers.Feature.Vector(new OpenLayers.Geometry.Polygon.createRegularPolygon
			(
				myLocation,
			    800, //radius, map units 800m 
			    40, // sides
			    0,
			));
			
			layers.overlay.addFeatures([layers.pointFeature, layers.circleFeature ]);
		
			map.addLayer(layers.overlay);

		
			// A popup with some information about our location
			layers.popup = new OpenLayers.Popup.Anchored("Popup", mapCenter,
					new OpenLayers.Size(60, 60),
					'It is right here', // this can be any html
					null, true // <--
																			// otherwise
			);

			// and add the popup to it.
			map.addPopup(layers.popup);
			
			
			
			
			var mapCentralMoveTo = function (mapcenter) {
				
				// update point feature
				layers.pointFeature.move(mapcenter);
				// update popup
				layers.popup.lonlat = mapcenter;
				layers.popup.updatePosition();

			}
			
		
			var updateEventHandler = function(){
				// update
				mapCenter = map.getCenter();

				mapCentralMoveTo(mapCenter);		
				// update form fields
				mapCenter.transform(layers.baseProjection,
						layers.defaultProjection);

				$('#ccpuriri_openlayers_lat').val(mapCenter.lat);
				$('#ccpuriri_openlayers_lon').val(mapCenter.lon);
				
			}
			
			// register events
			
			map.events.register("move", null, updateEventHandler);
			map.events.register("zoomend", null, updateEventHandler);
			
			
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
			
	
	
			
		}
	};

})(jQuery);