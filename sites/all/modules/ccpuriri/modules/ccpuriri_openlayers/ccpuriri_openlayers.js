(function($) {

	// declare a global object which is initialized by attach
	Drupal.ccpuriri = Drupal.ccpuriri || {};
	Drupal.ccpuriri.openlayers = Drupal.ccpuriri.openlayers || {};
		

	/**
	 * Attaches the openlayers behavior 
	 */
	Drupal.behaviors.CCPURIRI_OPENLAYERS = {
	  attach: function (context, settings) {
		  
		 var central = settings.ccpuriri_openlayers.center;
		  
		 // create the container project
		 Drupal.ccpuriri.openlayers.container = new Drupal.ccpuriri.openlayers(central.lon,central.lat);
		  
	  }
	};
	
	Drupal.ccpuriri.openlayers = function (lon,lat){
		var _openlayers =this;
		
		_openlayers.map =  new OpenLayers.Map("map");

		_openlayers.zoom = 15;// default
		
		_openlayers.CreateProjections();
		
		_openlayers.CreateBaseLayer();
		
		_openlayers.MapShow(lon, lat);
		
	}
	Drupal.ccpuriri.openlayers.prototype.CreateProjections = function(){
		
		var _openlayers =this;
	     
		_openlayers.defaultProjection = new OpenLayers.Projection("EPSG:4326");   // Transform from WGS 1984
	     _openlayers.baseProjection = new OpenLayers.Projection("EPSG:900913"); // to Spherical Mercator Projection
		
	};
	
	Drupal.ccpuriri.openlayers.prototype.CreateBaseLayer = function(){
		
		// This needs to be implemented by different map provider 
		
	};
	
	Drupal.ccpuriri.openlayers.prototype.MapShow =function(lon,lat){
		
		   var myLocation = 
			   new OpenLayers.LonLat(lon, lat).transform(
					   this.defaultProjection, this.baseProjection);
	
           this.map.setCenter(myLocation, this.zoom); 
           
	};

})(jQuery);