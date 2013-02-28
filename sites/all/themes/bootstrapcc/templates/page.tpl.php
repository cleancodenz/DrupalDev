 <!--header bar-->
    <div class="navbar navbar-inverse navbar-fixed-top">
        <div class="navbar-inner">
            <div class="container-fluid">
                <a class="btn btn-navbar" data-toggle="collapse" data-target=".nav-collapse"><span
                    class="icon-bar"></span><span class="icon-bar"></span><span class="icon-bar"></span>
                </a>
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
    </div>
    <!-- /.navbar -->
    
     <!--header -->
    <div class="navbar header">
        <div class="row-fluid">
            <div class="span4">
            <?php if (!empty($logo)): ?>
                <a class="brand" href="<?php print $front_page; ?>" 
                title="<?php print t('Home'); ?>">
                 <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
                 
                 <?php if (!empty($site_name)): ?>
                 <?php print $site_name; ?>
                 
                 <?php endif; ?>
                 </a>
            <?php endif; ?>
                    
            </div>
            <div class="span8">
                <div class="row-fluid">
                    <form class="navbar-search span5" action="">
                    <input type="text" class="search-query span12" placeholder="Search">
                    </form>
                </div>
            </div>
        </div>
        <hr>
    </div>
    