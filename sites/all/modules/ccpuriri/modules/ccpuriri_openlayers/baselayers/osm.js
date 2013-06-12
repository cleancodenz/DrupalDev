(function($) {
		
	Drupal.ccpuriri.openlayers.prototype.CreateBaseLayer =function(){
		// This needs to be implemented by different map provider 
		// set the base layer and default zoom
		
		this.zoom = 15;
		
	    this.map.addLayer(new OpenLayers.Layer.OSM());
        
	}
	
	
})(jQuery);