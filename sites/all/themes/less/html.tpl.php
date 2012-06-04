<!doctype html>
<html lang="en">

	<head>
		<meta charset="utf-8"/>
		<title><?php print $head_title; ?></title>
	
		<!--[if lt IE 9]>
			<script src="http://html5shim.googlecode.com/svn/trunk/html5.js"></script>
		<![endif]-->
		

		  <?php print $styles; ?>
  <?php print $scripts; ?>
		<meta name="viewport" content="width=device-width; initial-scale=1"/>
		<!-- Add "maximum-scale=1" to fix the Mobile Safari auto-zoom bug on orientation changes, 
			but keep in mind that it will disable user-zooming completely. Bad for accessibility. -->
		<script src="http://ajax.googleapis.com/ajax/libs/jquery/1.4.3/jquery.min.js"></script>
	</head>

	<body class="<?php print $classes; ?>" <?php print $attributes;?>>

<div id="skip-link"> <a href="#main-content" class="element-invisible element-focusable"><?php print t('Skip to main content'); ?></a></div>
  <?php print $page_top; ?>
  <?php print $page; ?>
  <?php print $page_bottom; ?>
</body>
</html>