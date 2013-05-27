(function($) {

	/**
	 * Fills the suggestion popup with any matches received. This is override of
	 * default implementation as the data structure is changed
	 * 
	 */
	Drupal.jsAC.prototype.found = function(matches) {
		// If no value in the textfield, do not show the popup.
		if (!this.input.value.length) {
			return false;
		}

		// Prepare matches.
		var ul = $('<ul></ul>');
		var ac = this;
		for (key in matches) {
			$('<li></li>').html($('<div></div>').html(key)).mousedown(
					function() {
						ac.select(this);
					}).mouseover(function() {
				ac.highlight(this);
			}).mouseout(function() {
				ac.unhighlight(this);
			}).data('autocompleteValue', key).data('autocompleteOtherValue',
					matches[key]).appendTo(ul);
		}

		// Show popup with matches, if any.
		if (this.popup) {
			if (ul.children().size()) {
				$(this.popup).empty().append(ul).show();
				$(this.ariaLive).html(Drupal.t('Autocomplete popup'));
			} else {
				$(this.popup).css({
					visibility : 'hidden'
				});
				this.hidePopup();
			}
		}
	};

	/**
	 * Puts the currently highlighted suggestion into the autocomplete field.
	 * this is override of select behaviour
	 */
	Drupal.jsAC.prototype.select = function(node) {
		this.input.value = $(node).data('autocompleteValue');
		var otherValue = $(node).data('autocompleteOtherValue');
		// updating other address field columns
		this.updateOther(otherValue);

	};

	/**
	 * Hides the autocomplete suggestions. this is override, the reason is it
	 * also populate the data
	 * 
	 */
	Drupal.jsAC.prototype.hidePopup = function(keycode) {
		// Select item if the right key or mousebutton was pressed.
		if (this.selected
				&& ((keycode && keycode != 46 && keycode != 8 && keycode != 27) || !keycode)) {
			this.input.value = $(this.selected).data('autocompleteValue');
			var otherValue = $(this.selected).data('autocompleteOtherValue');
			// updating other address field columns
			this.updateOther(otherValue);
		}
		// Hide popup.
		var popup = this.popup;
		if (popup) {
			this.popup = null;
			$(popup).fadeOut('fast', function() {
				$(popup).remove();
			});
		}
		this.selected = false;
		$(this.ariaLive).empty();
	};

	/**
	 * New function, update other columns of address field
	 * 
	 */
	Drupal.jsAC.prototype.updateOther = function(otherVaule) {

		// update unit
		if (otherVaule.sub_premise) {
			$('#edit-field-ccpuriri-addressfield-und-0-sub-premise').val(
					otherVaule.sub_premise);
		}
		// update street number
		if (otherVaule.premise) {
			$('#edit-field-ccpuriri-addressfield-und-0-premise').val(
					otherVaule.premise);
		}

		// update street
		if (otherVaule.thoroughfare) {
			$('#edit-field-ccpuriri-addressfield-und-0-thoroughfare').val(
					otherVaule.thoroughfare);
		}

		// update suburb
		if (otherVaule.dependent_locality) {
			$('#edit-field-ccpuriri-addressfield-und-0-dependent-locality')
					.val(otherVaule.dependent_locality);
		}

		// update city
		if (otherVaule.locality) {
			$('#edit-field-ccpuriri-addressfield-und-0-locality').val(
					otherVaule.locality);
		}

		// update postalcode
		if (otherVaule.postal_code) {
			$('#edit-field-ccpuriri-addressfield-und-0-postal-code').val(
					otherVaule.postal_code);
		}

		// update subadministrativearea
		if (otherVaule.sub_administrative_area) {
			$('#edit-field-ccpuriri-addressfield-und-0-sub-administrative-area').val(
					otherVaule.sub_administrative_area);
		}

		// update administrativearea
		if (otherVaule.administrative_area) {
			$('#edit-field-ccpuriri-addressfield-und-0-administrative-area').val(
					otherVaule.administrative_area);
		}
		
		
		// update country
		if (otherVaule.country) {
			$('#edit-field-ccpuriri-addressfield-und-0-country').val(
					otherVaule.country);
		}

	};

	/**
	 * Performs a cached and delayed search. This is override that uses post,
	 * and only starts search from 4 chars
	 */
	Drupal.ACDB.prototype.search = function(searchString) {
		var db = this;
		this.searchString = searchString;

		// See if this string needs to be searched for anyway.
		searchString = searchString.replace(/^\s+|\s+$/, '');
		if (searchString.length <= 3
				|| searchString.charAt(searchString.length - 1) == ',') {
			return;
		}

		// See if this key has been searched for before.
		if (this.cache[searchString]) {
			return this.owner.found(this.cache[searchString]);
		}

		// Initiate delayed search.
		if (this.timer) {
			clearTimeout(this.timer);
		}
		this.timer = setTimeout(function() {
			db.owner.setStatus('begin');

			// Ajax GET request for autocompletion.
			$.ajax({
				type : 'POST',
				url : db.uri,
				data : {
					search : searchString
				},
				dataType : 'json',
				success : function(matches) {
					if (typeof matches.status == 'undefined'
							|| matches.status != 0) {
						db.cache[searchString] = matches;
						// Verify if these are still the matches the user wants
						// to see.
						if (db.searchString == searchString) {
							db.owner.found(matches);
						}
						db.owner.setStatus('found');
					}
				},
				error : function(xmlhttp) {
					alert(Drupal.ajaxError(xmlhttp, db.uri));
				}
			});
		}, this.delay);
	};

})(jQuery);