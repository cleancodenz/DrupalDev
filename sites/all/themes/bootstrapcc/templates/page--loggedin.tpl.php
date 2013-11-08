<?php include 'page-header.php'; ?>


<div class="container cp-docs-container">
	<div class="row">

		<aside class="col-md-3" role="complementary">
		    <?php if (!empty($page['sidebar_first'])): ?>
			  <?php print render($page['sidebar_first']); ?>
			 <!-- /#sidebar-first -->
		    <?php endif; ?>
			  
		</aside>
		
		<section class="col-md-6" role="main">

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

	
		<aside class="col-md-2" role="complementary">
			<?php if (!empty($page['sidebar_second'])): ?>
			  <?php print render($page['sidebar_second']); ?>
				<!-- /#sidebar-second -->
		    <?php endif; ?>
	  
		</aside>
		
	</div>
	<footer class="footer">
		<?php print render($page['footer']); ?>
	</footer>
</div>

