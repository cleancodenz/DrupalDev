(function($) {

	// declare a global object which is initialized by attach
	Drupal.ccpuriri = Drupal.ccpuriri || {};
	Drupal.ccpuriri.addressfield = Drupal.ccpuriri.addressfield || {};

	// declare an event address changed event
	// interface is
	// $(Drupal.ccpuriri).trigger(Drupal.ccpuriri.AddressChangeEvent,
	// otherVaule.lon,// lon
	// otherVaule.lat,// lat
	// );
	Drupal.ccpuriri.AddressChangeEvent = 'ccpuriri_address_changed';

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
		var ul = $('<ul class="dropdown-menu"></ul>');
		var ac = this;
		ul.css({
			display : 'block',
			right : 0
		});
		for (key in matches) {
			$('<li></li>').html(
					$('<a href="#"></a>').html(key).click(function(e) {
						e.preventDefault();
					})).mousedown(function() {
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
			if (ul.children().length) {
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
			$('[name="field_ccpuriri_addressfield[und][0][sub_premise]"]').val(
					otherVaule.sub_premise);
		}
		// update street number
		if (otherVaule.premise) {
			$('[name="field_ccpuriri_addressfield[und][0][premise]"]').val(
					otherVaule.premise);
		}

		// update street
		if (otherVaule.thoroughfare) {
			$('[name="field_ccpuriri_addressfield[und][0][thoroughfare]"]')
					.val(otherVaule.thoroughfare);
		}

		// update suburb
		if (otherVaule.dependent_locality) {
			$(
					'[name="field_ccpuriri_addressfield[und][0][dependent_locality]"]')
					.val(otherVaule.dependent_locality);
		}

		// update city
		if (otherVaule.locality) {
			$('[name="field_ccpuriri_addressfield[und][0][locality]"]').val(
					otherVaule.locality);
		}

		// update postalcode
		if (otherVaule.postal_code) {
			$('[name="field_ccpuriri_addressfield[und][0][postal_code]"]').val(
					otherVaule.postal_code);
		}

		// update subadministrativearea
		if (otherVaule.sub_administrative_area) {
			$(
					'[name="field_ccpuriri_addressfield[und][0][sub_administrative_area]"]')
					.val(otherVaule.sub_administrative_area);
		}

		// update administrativearea
		if (otherVaule.administrative_area) {
			$(
					'[name="field_ccpuriri_addressfield[und][0][administrative_area]"]')
					.val(otherVaule.administrative_area);
		}

		// update country
		if (otherVaule.country) {
			$('[name="field_ccpuriri_addressfield[und][0][country]"]').val(
					otherVaule.country);
		}

		// lat and lon will be updated by map

		// update lat
		if (otherVaule.lat) {
			$('[name="field_ccpuriri_addressfield[und][0][lat]"]').val(
					otherVaule.lat);
		}

		// update lon
		if (otherVaule.lon) {
			$('[name="field_ccpuriri_addressfield[und][0][lon]"]').val(
					otherVaule.lon);
		}

		// trigger event, to tell map move

		$(Drupal.ccpuriri).trigger(Drupal.ccpuriri.AddressChangeEvent, {
			'lon' : otherVaule.lon,
			'lat' : otherVaule.lat
		});

	};

	/**
	 * Performs a cached and delayed search. This is override that uses post,
	 * and only starts search from 4 chars
	 */
	Drupal.ACDB.prototype.search = function(searchString) {
		var db = this;
		this.searchString = searchString;

		// extend the delay to 1 second
		this.delay = 1000;

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
