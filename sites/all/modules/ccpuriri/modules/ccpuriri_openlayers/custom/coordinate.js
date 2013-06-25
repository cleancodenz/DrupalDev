(function($) {
	
	/**
	 * Attaches the openlayers behavior
	 * This will display a marker in the control, when map moves the coordinate is updated  
	 */
	Drupal.behaviors.CCPURIRI_OPENLAYERS_COORDINATE = {
	  attach: function (context, settings) {
		  
		// get the container project
		var layers =  Drupal.ccpuriri.openlayers.layers;
		 
		var map = Drupal.ccpuriri.openlayers.layers.map ;
		
		var mapCenter = map.getCenter();
		    
        var myLocation = new OpenLayers.Geometry.Point(mapCenter.lon, mapCenter.lat);
        
		  
	      // The overlay layer for our marker, with a simple diamond as symbol
	    layers.overlay = new OpenLayers.Layer.Vector('Overlay', {
              styleMap: new OpenLayers.StyleMap({
                  externalGraphic: 'http://www.openlayers.org/dev/img/marker-gold.png',
                  graphicWidth: 20, graphicHeight: 24, graphicYOffset: -24,
                  title: '${tooltip}'
              })
          });

          // We add the marker with a tooltip text to the overlay
	    layers.pointFeature = new OpenLayers.Feature.Vector(myLocation, { tooltip: 'OpenLayers' });

	    layers.overlay.addFeatures([layers.pointFeature]);
                   

        map.addLayer(layers.overlay);

	    
 
          // A popup with some information about our location
        layers.popup = new OpenLayers.Popup.Anchored("Popup",
                  mapCenter, new OpenLayers.Size(100,100),
                      '<a target="_blank" href="http://openlayers.org/">We</a> ' +
                      'could be here.<br>Or elsewhere.', null,
                  true // <-- true if we want a close (X) button, false otherwise
           );

    
          // and add the popup to it.
          map.addPopup(layers.popup);

          // register events

          map.events.register("move", null, function(){
        	  // update 
        	  mapCenter = map.getCenter();
        	  
        	  // update point feature 
    		  layers.pointFeature.move(mapCenter);
              // update popup
    		  layers.popup.lonlat = mapCenter;
    		  layers.popup.updatePosition();
    		  
    		  // update form fields
    		  mapCenter.transform(layers.baseProjection,
    				  layers.defaultProjection);
  	  
					   
    		  $('#ccpuriri_openlayers_lat').val(mapCenter.lat);
    		  $('#ccpuriri_openlayers_lon').val(mapCenter.lon);
    		  
        	  
          }  );
          
	  }
	};

})(jQuery);