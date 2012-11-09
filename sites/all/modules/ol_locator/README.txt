
-- SUMMARY --

The OpenLayers Locator is a feature package that creates a robust, 
turn-key Locator using the Openlayers, Openlayers Proximity, Addressfield, 
Geofield and Geocoder modules.

For a full description of the module, visit the project page:

http://drupal.org/sandbox/nicoz/1303200

To submit bug reports and feature suggestions, or to track changes:

http://drupal.org/node/add/project-issue/1303200


-- REQUIREMENTS --

Modules:

Features
http://drupal.org/project/features

OpenLayers 
http://www.drupal.org/project/openlayers

OpenLayers Proximity (Currently in Sandbox) 
http://drupal.org/sandbox/jpstrikesback/1367194

Views
http://www.drupal.org/project/views

Chaos tools
http://www.drupal.org/project/ctools

Address Field
http://drupal.org/project/addressfield

Geocoder API
http://drupal.org/project/geocoder

Geofield
http://drupal.org/project/geofield

Libraries API
http://drupal.org/project/libraries

Libraries:
GeoPHP library
https://github.com/phayes/geoPHP


-- INSTALLATION --

* Download all required modules and place them in your modules folder 
(usually /sites/all/modules).

* Download and place the GeoPHP library and place it in sites/all/libraries 
(should look like /sites/all/libraries/geoPHP). 

* Enable OpenLayers Locator at admin/modules 
(will prompt you enable all dependencies).

* Optional: Enable Views UI and OpenLayers UI (Submodules of the the 
respective parent modules). These will be required to customize your 
views and maps.


-- CONFIGURATION --

* Configure user permissions in Administration > People > Permissions 
(/admin/people/permissions).

	Location: Create new content
	Location: Edit own content
	Location: Edit any content
	Location: Delete own content
	Location: Delete any content
	Administer features: Perform administration tasks on features.
	Manage features: View, enable and disable features. 

*Optional (if Views UI and OpenLayers UI are enabled)
	Administer views: Access the views administration pages.
	Bypass views access control: Bypass access control when accessing views.
	Administer OpenLayers: Configure OpenLayers settings, styles, maps, and layers.
 

-- CUSTOMIZATION --

*To customize the Maps:

1) Navigate to Structure > OpenLayers > Maps 
   (/admin/structure/openlayers/maps).

2) Choose which map to clone and press clone. 

3) Make Customizations

*To customize the Data (Views):

1) Navigate to Structure > Views

2) Click 'edit' on OpenLayers Locator proximity search

3) Make customizations

Please note that any of these customizations will override the default 
settings provided by this module and will store your customizations 
in the database. To undo your changes, click 'revert' on the view and
it will return to it's original state.


-- TROUBLESHOOTING --

none.


-- FAQ --

none.


-- CONTACT --

Current maintainers:
*Nico Zdunich (nicoz) - http://drupal.org/user/693674

This project has been sponsored by:
*Pixel Sweatshop - http://www.pixelsweatshop.com