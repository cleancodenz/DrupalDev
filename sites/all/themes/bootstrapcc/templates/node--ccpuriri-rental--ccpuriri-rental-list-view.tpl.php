
<div id="node-<?php print $node->nid; ?>"
	class="<?php print $classes; ?> clearfix" <?php print $attributes; ?>>
	<div class="container">
		<div class="row">
			<div class="col-md-2"></div>
			<div class="col-md-4">
				<header>
					<?php print render($title_prefix); ?>
					<?php if (!$page && $title): ?>
					<h2 <?php print $title_attributes; ?>>
						<a href="<?php print $node_url; ?>"><?php print $title; ?> </a>
					</h2>
					<?php endif; ?>
					<?php print render($title_suffix); ?>

					<?php if ($display_submitted): ?>
					<span class="submitted"> fffff <?php print $user_picture; ?> <?php print $submitted; ?>
					</span>
					<?php endif; ?>
				</header>

				<?php
				// Hide comments, tags, and links now so that we can render them later.
				hide($content['comments']);
				hide($content['links']);
				hide($content['field_tags']);
				print render($content);
				?>

				<?php if (!empty($content['field_tags']) || !empty($content['links'])): ?>
				<footer>
					<?php print render($content['field_tags']); ?>
					<?php print render($content['links']); ?>
				</footer>
				<?php endif; ?>

				<?php print render($content['comments']); ?>
			</div>
		</div>

	</div>
</div>
<!-- /.node -->
