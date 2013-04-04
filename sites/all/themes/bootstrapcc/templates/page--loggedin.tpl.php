
<!--header
three columns
  bar-->
<header
	class="navbar navbar-inverse navbar-fixed-top">
	<div class="navbar-inner">
		<div class="container-fluid">
			<a class="btn btn-navbar" data-toggle="collapse"
				data-target=".nav-collapse"><span class="icon-bar"></span><span
				class="icon-bar"></span><span class="icon-bar"></span> </a>
			<?php if (!empty($primary_nav) || !empty($secondary_nav)): ?>
			<div class="nav-collapse">
				<?php if (!empty($primary_nav)): ?>
				<?php print render($primary_nav); ?>
				<?php endif; ?>

				<?php if (!empty($secondary_nav)): ?>
				<?php print render($secondary_nav); ?>
				<?php endif; ?>
			</div>
			<?php endif; ?>
			<!-- /.nav-collapse -->
		</div>
		<!-- /.container -->
	</div>
	<!-- /.navbar-inner -->
</header>
<!-- /.navbar -->

<!--header -->
<div class="navbar header">
	<div class="row-fluid">
		<div class="span4">

			<?php if (!empty($logo)): ?>
			<a class="brand" href="<?php print $front_page; ?>"
				title="<?php print t('Home'); ?>"> <img src="<?php print $logo; ?>"
				alt="<?php print t('Home'); ?>" /> <?php if (!empty($site_name)): ?>
				<?php print $site_name; ?> <?php endif; ?>
			</a>
			<?php endif; ?>

		</div>
		<div class="span8">
			<div class="row-fluid">
				<?php if (!empty($page['header'])): ?>
				<?php print render($page['header']); ?>
				<!-- /#header normally just search-->
				<?php endif; ?>
			</div>
		</div>
	</div>
	<hr>
</div>

<div class="container-fluid main">
	<div class="row-fluid">

		<?php if (!empty($page['sidebar_first'])): ?>
		<aside class="span2" role="complementary">
			<?php print render($page['sidebar_first']); ?>
		</aside>
		<!-- /#sidebar-first -->
		<?php endif; ?>

		<section class="<?php print _bootstrapcc_content_span($columns); ?>"
			style="margin-left:19px">

			<?php if (!empty($breadcrumb)): print $breadcrumb; endif;?>
			<!-- /#breadcrumb -->

			<a id="main-content"></a>
			<?php print render($title_prefix); ?>
		
			<?php print render($title_suffix); ?>
			<?php print $messages; ?>
			<?php if (!empty($tabs)): ?>
			<?php print render($tabs); ?>
			<?php endif; ?>
			<?php if (!empty($page['help'])): ?>
			<div class="well">
				<?php print render($page['help']); ?>
			</div>
			<?php endif; ?>
			<?php if (!empty($action_links)): ?>
			<ul class="action-links">
				<?php print render($action_links); ?>
			</ul>
			<?php endif; ?>

			<?php print render($page['content']); ?>
			<!-- /#content -->

		</section>

		<?php if (!empty($page['sidebar_second'])): ?>
		<aside class="span2" role="complementary">
			<?php print render($page['sidebar_second']); ?>
		</aside>
		<!-- /#sidebar-second -->
		<?php endif; ?>
		
	</div>
	<footer class="footer">
		<?php print render($page['footer']); ?>
	</footer>
</div>

