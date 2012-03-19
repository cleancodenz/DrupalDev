<?php 
function form_example_tutorial() {
	return t('This is a set of nine form tutorials tied to the <a href="http://drupal.org/node/262422">Drupal handbook</a>.');
}

function form_example_tutorial_1($form, &$form_state) {

	$form['description'] = array(
			'#type' => 'item',
			'#title' => t('A form with nothing but a textfield'),
	);
	// This is the first form element. It's a textfield with a label, "Name"
	$form['name'] = array(
			'#type' => 'textfield',
			'#title' => t('Name'),
	);
	return $form;

}


function form_example_tutorial_2($form, &$form_state) {
	$form['description'] = array(
			'#type' => 'item',
			'#title' => t('A simple form with a submit button'),
	);

	$form['name'] = array(
			'#type' => 'textfield',
			'#title' => t('Name'),
	);

	// Adds a simple submit button that refreshes the form and clears its
	// contents. This is the default behavior for forms.
	$form['submit'] = array(
			'#type' => 'submit',
			'#value' => 'Submit',
	);
	return $form;
}


function form_example_tutorial_3($form, &$form_state) {
	$form['description'] = array(
			'#type' => 'item',
			'#title' => t('A form with a fieldset'),
	);

	$form['name'] = array(
			'#type' => 'fieldset',
			'#title' => t('Name'),
	);
	$form['name']['first'] = array(
			'#type' => 'textfield',
			'#title' => t('First name'),
	);
	$form['name']['last'] = array(
			'#type' => 'textfield',
			'#title' => t('Last name'),
	);


	$form['submit'] = array(
			'#type' => 'submit',
			'#value' => 'Submit',
	);
	return $form;
}

function form_example_tutorial_4($form, &$form_state) {
	$form['description'] = array(
			'#type' => 'item',
			'#title' => t('A form with validation'),
	);

	$form['name'] = array(
			'#type' => 'fieldset',
			'#title' => t('Name'),
			// Make the fieldset collapsible.
			'#collapsible' => TRUE, // Added
			'#collapsed' => FALSE, // Added
	);

	// Make these fields required.
	$form['name']['first'] = array(
			'#type' => 'textfield',
			'#title' => t('First name'),
			'#required' => TRUE, // Added
	);
	$form['name']['last'] = array(
			'#type' => 'textfield',
			'#title' => t('Last name'),
			'#required' => TRUE, // Added
	);

	$form['submit'] = array(
			'#type' => 'submit',
			'#value' => 'Submit',
	);
	return $form;
}


function form_example_tutorial_5($form, &$form_state) {
	$form['description'] = array(
			'#type' => 'item',
			'#title' => t('A form with additional attributes'),
			'#description' => t('This one adds #default_value and #description'),
	);
	$form['name'] = array(
			'#type' => 'fieldset',
			'#title' => t('Name'),
			'#collapsible' => TRUE,
			'#collapsed' => FALSE,
	);

	$form['name']['first'] = array(
			'#type' => 'textfield',
			'#title' => t('First name'),
			'#required' => TRUE,
			'#default_value' => "First name", // added default value.
			'#description' => "Please enter your first name.", // added description
			'#size' => 20, // added
			'#maxlength' => 20, // added
	);
	$form['name']['last'] = array(
			'#type' => 'textfield',
			'#title' => t('Last name'),
			'#required' => TRUE,
	);
	$form['submit'] = array(
			'#type' => 'submit',
			'#value' => 'Submit',
	);
	return $form;
}

function form_example_tutorial_6($form, &$form_state) {
	$form['description'] = array(
			'#type' => 'item',
			'#title' => t('A form with a validation handler'),
	);

	$form['name'] = array(
			'#type' => 'fieldset',
			'#title' => t('Name'),
			'#collapsible' => TRUE,
			'#collapsed' => FALSE,
	);
	$form['name']['first'] = array(
			'#type' => 'textfield',
			'#title' => t('First name'),
			'#required' => TRUE,
			'#default_value' => "First name",
			'#description' => "Please enter your first name.",
			'#size' => 20,
			'#maxlength' => 20,
	);
	$form['name']['last'] = array(
			'#type' => 'textfield',
			'#title' => t('Last name'),
			'#required' => TRUE,
	);

	// New form field added to permit entry of year of birth.
	// The data entered into this field will be validated with
	// the default validation function.
	$form['year_of_birth'] = array(
			'#type' => 'textfield',
			'#title' => "Year of birth",
			'#description' => 'Format is "YYYY"',
	);

	$form['submit'] = array(
			'#type' => 'submit',
			'#value' => 'Submit',
	);
	return $form;
}

function form_example_tutorial_6_validate($form, &$form_state) {
	$year_of_birth = $form_state['values']['year_of_birth'];
	if ($year_of_birth && ($year_of_birth < 1900 || $year_of_birth > 2000)) {
		form_set_error('year_of_birth', t('Enter a year between 1900 and 2000.'));
	}
}


function form_example_tutorial_7($form, &$form_state) {
	$form['description'] = array(
			'#type' => 'item',
			'#title' => t('A form with a submit handler'),
	);
	$form['name'] = array(
			'#type' => 'fieldset',
			'#title' => t('Name'),
			'#collapsible' => TRUE,
			'#collapsed' => FALSE,
	);
	$form['name']['first'] = array(
			'#type' => 'textfield',
			'#title' => t('First name'),
			'#required' => TRUE,
			'#default_value' => "First name",
			'#description' => "Please enter your first name.",
			'#size' => 20,
			'#maxlength' => 20,
	);
	$form['name']['last'] = array(
			'#type' => 'textfield',
			'#title' => t('Last name'),
			'#required' => TRUE,
	);
	$form['year_of_birth'] = array(
			'#type' => 'textfield',
			'#title' => "Year of birth",
			'#description' => 'Format is "YYYY"',
	);
	$form['submit'] = array(
			'#type' => 'submit',
			'#value' => 'Submit',
	);
	return $form;
}

function form_example_tutorial_7_validate($form, &$form_state) {
	$year_of_birth = $form_state['values']['year_of_birth'];
	if ($year_of_birth && ($year_of_birth < 1900 || $year_of_birth > 2000)) {
		form_set_error('year_of_birth', t('Enter a year between 1900 and 2000.'));
	}
}


function form_example_tutorial_7_submit($form, &$form_state) {
	drupal_set_message(t('The form has been submitted. name="@first @last", year of birth=@year_of_birth',
			array('@first' => $form_state['values']['first'], '@last' => $form_state['values']['last'], '@year_of_birth' => $form_state['values']['year_of_birth'])));
}

function form_example_tutorial_8($form, &$form_state) {

	// Display page 2 if $form_state['page_num'] == 2
	if (!empty($form_state['page_num']) && $form_state['page_num'] == 2) {
		return form_example_tutorial_8_page_two($form, $form_state);
	}

	// Otherwise we build page 1.
	$form_state['page_num'] = 1;

	$form['description'] = array(
			'#type' => 'item',
			'#title' => t('A basic multistep form (page 1)'),
	);

	$form['first'] = array(
			'#type' => 'textfield',
			'#title' => t('First name'),
			'#description' => "Please enter your first name.",
			'#size' => 20,
			'#maxlength' => 20,
			'#required' => TRUE,
			'#default_value' => !empty($form_state['values']['first']) ? $form_state['values']['first'] : '',
	);
	$form['last'] = array(
			'#type' => 'textfield',
			'#title' => t('Last name'),
			'#default_value' => !empty($form_state['values']['last']) ? $form_state['values']['last'] : '',
	);
	$form['year_of_birth'] = array(
			'#type' => 'textfield',
			'#title' => "Year of birth",
			'#description' => 'Format is "YYYY"',
			'#default_value' => !empty($form_state['values']['year_of_birth']) ? $form_state['values']['year_of_birth'] : '',
	);
	$form['next'] = array(
			'#type' => 'submit',
			'#value' => 'Next >>',
			'#submit' => array('form_example_tutorial_8_next_submit'),
			'#validate' => array('form_example_tutorial_8_next_validate'),
	);
	return $form;
}

function form_example_tutorial_8_next_validate($form, &$form_state) {
	$year_of_birth = $form_state['values']['year_of_birth'];
	if ($year_of_birth && ($year_of_birth < 1900 || $year_of_birth > 2000)) {
		form_set_error('year_of_birth', t('Enter a year between 1900 and 2000.'));
	}
}

function form_example_tutorial_8_next_submit($form, &$form_state) {

	// Values are saved for each page.
	// to carry forward to subsequent pages in the form.
	// and we tell FAPI to rebuild the form.
	$form_state['page_values'][1] = $form_state['values'];

	if (!empty($form_state['page_values'][2])) {
		$form_state['values'] = $form_state['page_values'][2];
	}

	// When form rebuilds, it will look at this to figure which page to build.
	$form_state['page_num'] = 2;
	$form_state['rebuild'] = TRUE;
}


function form_example_tutorial_8_page_two($form, &$form_state) {
	$form['description'] = array(
			'#type' => 'item',
			'#title' => t('A basic multistep form (page 2)'),
	);

	$form['color'] = array(
			'#type' => 'textfield',
			'#title' => t('Favorite color'),
			'#required' => TRUE,
			'#default_value' => !empty($form_state['values']['color']) ? $form_state['values']['color'] : '',
	);
	$form['submit'] = array(
			'#type' => 'submit',
			'#value' => t('Submit'),
			'#submit' => array('form_example_tutorial_8_page_two_submit'),
	);
	$form['back'] = array(
			'#type' => 'submit',
			'#value' => t('<< Back'),
			'#submit' => array('form_example_tutorial_8_page_two_back'),
			// We won't bother validating the required 'color' field, since they
	// have to come back to this page to submit anyway.
			'#limit_validation_errors' => array(),
	);
	return $form;
}

function form_example_tutorial_8_page_two_back($form, &$form_state) {
	$form_state['values'] = $form_state['page_values'][1];
	$form_state['page_num'] = 1;
	$form_state['rebuild'] = TRUE;
}

function form_example_tutorial_8_page_two_submit($form, &$form_state) {
	// Normally, some code would go here to alter the database with the data
	// collected from the form. Instead sets a message with drupal_set_message()
	// to validate that the code worked.
	$page_one_values = $form_state['page_values'][1];
	drupal_set_message(t('The form has been submitted. name="@first @last", year of birth=@year_of_birth',
			array('@first' => $page_one_values['first'], '@last' => $page_one_values['last'], '@year_of_birth' => $page_one_values['year_of_birth'])));

	if (!empty($page_one_values['first2'])) {
		drupal_set_message(t('Second name: name="@first @last", year of birth=@year_of_birth',
				array('@first' => $page_one_values['first2'], '@last' => $page_one_values['last2'], '@year_of_birth' => $page_one_values['year_of_birth2'])));
	}
	drupal_set_message(t('And the favorite color is @color', array('@color' => $form_state['values']['color'])));

	// If we wanted to redirect on submission, set $form_state['redirect']
	// $form_state['redirect'] = 'node'; // Redirects the user to /node.
}





