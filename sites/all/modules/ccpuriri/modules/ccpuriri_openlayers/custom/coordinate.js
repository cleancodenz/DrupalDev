(function($) {

	/**
	 * Attaches the openlayers behavior
	 * This will display a marker in the control, when map moves the coordinate is updated  
	 */
	Drupal.behaviors.CCPURIRI_OPENLAYERS_COORDINATE = {
	  attach: function (context, settings) {
		  
		// get the container project
		 var container =  Drupal.ccpuriri.openlayers.container;
		 
		 var map = Drupal.ccpuriri.openlayers.container.map ;
		
	    var mapCenter = map.getCenter();
	    
	      // The overlay layer for our marker, with a simple diamond as symbol
	    container.overlay = new OpenLayers.Layer.Vector('Overlay', {
              styleMap: new OpenLayers.StyleMap({
                  externalGraphic: '../img/marker.png',
                  graphicWidth: 20, graphicHeight: 24, graphicYOffset: -24,
                  title: '${tooltip}'
              })
          });

          // We add the marker with a tooltip text to the overlay
	    container.pointFeature = new OpenLayers.Feature.Vector(myLocation, { tooltip: 'OpenLayers' });

	    container.overlay.addFeatures([container.pointFeature]);
                   

        map.addLayer(container.overlay);

 
          // A popup with some information about our location
        container.popup = new OpenLayers.Popup.FramedCloud("Popup",
                  mapCenter, null,
                      '<a target="_blank" href="http://openlayers.org/">We</a> ' +
                      'could be here.<br>Or elsewhere.', null,
                  true // <-- true if we want a close (X) button, false otherwise
           );


          // and add the popup to it.
          map.addPopup(container.popup);

          // register events

          map.events.register("move", null, Drupal.ccpuriri.openlayers.displayCenter);
		  
	  }
	};
	
	Drupal.ccpuriri.openlayers.displayCenter = function()
	{
		  var mapCenter = map.getCenter();
		  var container =  Drupal.ccpuriri.openlayers.container;
		  
          // update point feature 
		  container.pointFeature.move(mapCenter);
          // update popup
		  container.popup.lonlat = mapCenter;
		  container.popup.updatePosition();
		
	}
})(jQuery);