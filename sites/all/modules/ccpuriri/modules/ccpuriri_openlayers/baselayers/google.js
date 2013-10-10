(function() {
		
	Drupal.ccpuriri.openlayers.Map.prototype.CreateBaseLayer =function(){
		// This needs to be implemented by different map provider 
		// set the base layer and default zoom
		   // funy thing is it knows these are baselayer while marker layer is treated as overlay
        
		this.zoom = 15;
		
		this.map.addLayer(new OpenLayers.Layer.Google(
                "Google Streets",
                { numZoomLevels: 20 }
            ));

        this.map.addLayer(new OpenLayers.Layer.Google(
                "Google Hybrid",
                { type: google.maps.MapTypeId.HYBRID, numZoomLevels: 20 }
            ));

        this.map.addLayer(new OpenLayers.Layer.Google(
                "Google Satellite",
                { type: google.maps.MapTypeId.SATELLITE, numZoomLevels: 22 }
            ));
        
	}
	
	
})();