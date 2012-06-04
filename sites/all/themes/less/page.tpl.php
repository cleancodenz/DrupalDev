<section id="main">

		<header id="page_top" class="page_top">
		<?php if ($logo): ?>
	  		<article id="logo_wrapper" class="logo_wrapper">
    			<h1 id="logo"><a href="<?php print check_url($front_page); ?>" title="<?php print t('Home'); ?>"<?php print $logo; ?></a></h1>
	 		</article>
		<?php endif; ?>
		
		<hgroup>
		
		<?php if ($site_name): ?>
    			<h1 id="site_name"><a href="<?php print check_url($front_page); ?>" title="<?php print t('Home'); ?>"><?php print $site_name; ?></a></h1> 
		<?php endif; ?>
		
		<?php if ($site_name): ?>
				<h2 id="site_slogan"><?php print $site_slogan; ?></h2>	
		<?php endif; ?>	
		
		</hgroup>
		

      <?php if ($main_menu): ?>
            <nav id="main-menu" class="navigation">

              <?php print theme('links__system_main_menu', array(
  
               'links' => $main_menu,
  
                'attributes' => array(
   
                  'id' => 'main-menu-links',
   
                  'class' => array('links', 'clearfix'),
   
                ),
   
                'heading' => array(
  
                  'text' => t('Main menu'),
  
                  'level' => 'h2',
  
                  'class' => array('element-invisible'),
  
                ),
  
              )); ?>
  
            </nav> <!-- /#main-menu -->
  
      <?php endif; ?>

		
		</header> <!-- /page_top -->
 		
		<section id="highlighted" class="highlighted">
	
		<?php print theme('grid_block', array('content' => $messages, 'id' => 'content-messages')); ?>
	
		</section> <!-- /highlighted -->   
	                              
		<section id="featured" class="featured"	>
	

		</section> <!-- /featured -->
	
		<section id="content" class="content">
    		<?php print theme('grid_block', array('content' => render($tabs), 'id' => 'content-tabs')); ?>
		<?php if ($title): ?><h1 class="title" id="page-title"><?php print $title; ?></h1><?php endif; ?>
    		<?php print render($page['content']); ?>
		</section> <!-- /content -->
	
		<section id="sidebar_first" class="sidebar_first">

			<?php print render($page['sidebar_first']); ?>


		</section>  <!-- /sidebar_first -->	
	

		<section id="sidebar_last" class="sidebar_last">

    		<?php print render($page['sidebar_last']); ?>

		</section>	<!-- /sidebar_last -->
	
	<footer id="footer" class="footer">
	
	</footer>
	
	</section>	<!-- /main -->
