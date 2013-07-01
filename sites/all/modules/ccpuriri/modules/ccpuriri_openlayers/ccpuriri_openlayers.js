(function() {

	// declare a global object which is initialized by attach
	Drupal.ccpuriri = Drupal.ccpuriri || {};
	Drupal.ccpuriri.openlayers = Drupal.ccpuriri.openlayers || {};
		

	/**
	 * Attaches the openlayers behavior 
	 */
	Drupal.behaviors.CCPURIRI_OPENLAYERS = {
	  attach: function (context, settings) {
		  
		 var central = settings.ccpuriri_openlayers.center;
		
		 var lat = central.lat;
		 var lon = central.lon;
		/* use of getCurrentPosition asks for permission
		if (lon==0 && lat ==0)
		{
			// this means geo is not set yet, always give it a default
			// first check browser geo 
			
			 if(navigator.geolocation)
			 {
				 var options = {
						  enableHighAccuracy: true,
						  timeout: 5000,
						  maximumAge: 0
						};
								
				navigator.geolocation.getCurrentPosition(
						 function(position){
							 lat = position.coords.latitude;
				             lon = position.coords.longitude;
						 },
						 function(err){
							 console.warn('ERROR(' + err.code + '): ' + err.message);
						 },
						 
						 options
				 );
				 
			 }
			
		}
		*/
		 
		if (lon==0 && lat ==0)
		{
			 // use the default system geo
			 lat = settings.ccpuriri_openlayers.default_center.lat;
			 
			 lon = settings.ccpuriri_openlayers.default_center.lon;
		
		}
		 // create the container project
		 Drupal.ccpuriri.openlayers.layers = new Drupal.ccpuriri.openlayers.Map(lon,lat);
		 
	
	  }
	};
	
	Drupal.ccpuriri.openlayers.Map = function (lon,lat){
		var _openlayers =this;
		
		_openlayers.map =  new OpenLayers.Map("map");

		_openlayers.zoom = 15;// default
		
		_openlayers.CreateProjections();
		
		_openlayers.CreateBaseLayer();
		
		_openlayers.MapShow(lon, lat);
		
	}
	
	Drupal.ccpuriri.openlayers.Map.prototype.CreateProjections = function(){
		
		var _openlayers =this;
	     
		_openlayers.defaultProjection = new OpenLayers.Projection("EPSG:4326");   // Transform from WGS 1984
	     _openlayers.baseProjection = new OpenLayers.Projection("EPSG:900913"); // to Spherical Mercator Projection
		
	};
	
	Drupal.ccpuriri.openlayers.Map.prototype.CreateBaseLayer = function(){
		
		// This needs to be implemented by different map provider 
		
	};
	
	Drupal.ccpuriri.openlayers.Map.prototype.MapShow =function(lon,lat){
		
		   var myLocation = 
			   new OpenLayers.LonLat(lon, lat).transform(
					   this.defaultProjection, this.baseProjection);
	
           this.map.setCenter(myLocation, this.zoom); 
           
	};

})();