
<!--header
three columns
  bar-->
<nav class="navbar navbar-inverse navbar-fixed-top" role="navigation">
	
	<!-- Brand and toggle get grouped for better mobile display -->
	<div class="navbar-header">
          <button type="button" class="navbar-toggle" data-toggle="collapse" data-target="#navbar-collapse-1">
            <span class="sr-only">Toggle navigation</span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
          </button>
      </div>
    <!-- Collect the nav links, forms, and other content for toggling -->
	<?php if (!empty($primary_nav) || !empty($secondary_nav)): ?>    
	
	<div class="collapse navbar-collapse" id="navbar-collapse-1">
    	<?php if (!empty($primary_nav)): ?>
				<?php print render($primary_nav); ?>
				<?php endif; ?>

				<?php if (!empty($secondary_nav)): ?>
				<?php print render($secondary_nav); ?>
				<?php endif; ?>    
    </div>
	<?php endif; ?>
	<!-- /.navbar-collapse -->
	
		
	
	
</nav>
<!-- /.navbar -->

<!--header for logo  -->
<div class="cp-header container">
  <div class="row">
		<div class="col-md-4">

			<?php if (!empty($logo)): ?>
			<a class="navbar-brand" href="<?php print $front_page; ?>"
				title="<?php print t('Home'); ?>"> <img src="<?php print $logo; ?>"
				alt="<?php print t('Home'); ?>" /> <?php if (!empty($site_name)): ?>
				<?php print $site_name; ?> <?php endif; ?>
			</a>
			<?php endif; ?>

		</div>
		<div class="col-md-8">
			<div class="row">
				<?php if (!empty($page['header'])): ?>
				<?php print render($page['header']); ?>
				<!-- /#header normally just search-->
				<?php endif; ?>
			</div>
		</div>
   </div>
  <hr/>
</div>


