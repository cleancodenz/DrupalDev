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
