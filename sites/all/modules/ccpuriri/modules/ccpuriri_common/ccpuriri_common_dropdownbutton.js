(function($) {

	// declare a global object which is initialized by attach
	Drupal.ccpuriri = Drupal.ccpuriri || {};
	Drupal.ccpuriri.dropdownbutton = Drupal.ccpuriri.dropdownbutton || {};

	Drupal.behaviors.DROPDOWNBUTTON = {
		attach : function(context, settings) {
			if (settings.dropdownbuttonids){
				 for (var base in settings.dropdownbuttonids) {
						// binding the select event to every li select
					$('#'+settings.dropdownbuttonids[base]+'-div > ul.dropdown-menu > li ').bind('click',function(){
						// set teh value to hidden input
						$('#'+settings.dropdownbuttonids[base]+'-div > input[type="hidden"]').val($(this).val());
						
						// trigger the ajax event
						$('#'+settings.dropdownbuttonids[base]).trigger('itemselected');
						
					});
						
					 
				 }
				
			}
			
			
		},

	};

})(jQuery);
