
(function ($) {
	
	/**
	 * Fills the suggestion popup with any matches received.
	 * This is override of default implementation as the data structure is changed
	 * 
	 */
	Drupal.jsAC.prototype.found = function (matches) {
	  // If no value in the textfield, do not show the popup.
	  if (!this.input.value.length) {
	    return false;
	  }

	  // Prepare matches.
	  var ul = $('<ul></ul>');
	  var ac = this;
	  for (key in matches) {
	    $('<li></li>')
	      .html($('<div></div>').html(key))
	      .mousedown(function () { ac.select(this); })
	      .mouseover(function () { ac.highlight(this); })
	      .mouseout(function () { ac.unhighlight(this); })
	      .data('autocompleteValue', key)
	      .data('autocompleteOtherValue', matches[key])
	      .appendTo(ul);
	  }

	  // Show popup with matches, if any.
	  if (this.popup) {
	    if (ul.children().size()) {
	      $(this.popup).empty().append(ul).show();
	      $(this.ariaLive).html(Drupal.t('Autocomplete popup'));
	    }
	    else {
	      $(this.popup).css({ visibility: 'hidden' });
	      this.hidePopup();
	    }
	  }
	};
	
	
	/**
	 * Puts the currently highlighted suggestion into the autocomplete field.
	 * this is override of select behaviour
	 */
	Drupal.jsAC.prototype.select = function (node) {
	  this.input.value = $(node).data('autocompleteValue');
	  var otherValue = $(node).data('autocompleteOtherValue');
	  // updating other address field columns
	  this.updateOther(otherValue); 
	  
	};
	
	/**
	 * Hides the autocomplete suggestions.
	 * this is override, the reason is it also populate the data
	 *
	 */
	Drupal.jsAC.prototype.hidePopup = function (keycode) {
	  // Select item if the right key or mousebutton was pressed.
	  if (this.selected && ((keycode && keycode != 46 && keycode != 8 && keycode != 27) || !keycode)) {
	    this.input.value = $(this.selected).data('autocompleteValue');
	    var otherValue = $(this.selected).data('autocompleteOtherValue');
		  // updating other address field columns
		  this.updateOther(otherValue); 
	  }
	  // Hide popup.
	  var popup = this.popup;
	  if (popup) {
	    this.popup = null;
	    $(popup).fadeOut('fast', function () { $(popup).remove(); });
	  }
	  this.selected = false;
	  $(this.ariaLive).empty();
	};
	
	
	/**
	 * New function, update other columns of address field
	 *
	 */
	Drupal.jsAC.prototype.updateOther = function (otherVaule) {
	 
		// update unit
		if (otherVaule.unit)
		{
			$('#edit-field-ccpuriri-addressfield-und-0-sub-premise').val(otherVaule.unit);
		}
		// update street number 
		if (otherVaule.streetnumber)
		{
			$('#edit-field-ccpuriri-addressfield-und-0-premise').val(otherVaule.streetnumber);
		}
	
		// update street 
		if (otherVaule.street)
		{
			$('#edit-field-ccpuriri-addressfield-und-0-thoroughfare').val(otherVaule.street);
		}
		
		// update suburb 
		if (otherVaule.suburb)
		{
			$('#edit-field-ccpuriri-addressfield-und-0-dependent-locality').val(otherVaule.suburb);
		}
		
		// update city 
		if (otherVaule.city)
		{
			$('#edit-field-ccpuriri-addressfield-und-0-locality').val(otherVaule.city);
		}
		
		// update postalcode 
		if (otherVaule.postalcode)
		{
			$('#edit-field-ccpuriri-addressfield-und-0-postal-code').val(otherVaule.postalcode);
		}
	
		// update postalcode 
		if (otherVaule.country)
		{
			$('#edit-field-ccpuriri-addressfield-und-0-country').val(otherVaule.country);
		}
		
	};
	
	
})(jQuery);