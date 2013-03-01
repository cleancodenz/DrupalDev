 <!--header

  bar-->
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
                    <form class="navbar-search span5" style="padding-top: 12px"  action="">
                    <input type="text" class="search-query span12" placeholder="Search">
                    </form>
                </div>
            </div>
        </div>
        <hr>
    </div>
    
 
    <div class="container-fluid main">
        <div class="row-fluid">
            <div class="span3">
                <div class="row-fluid">
                    <ul class="nav nav-list  cc-sidenav">
                        <li class=""><a href="#dropdowns"><i class="icon-chevron-right"></i>Dropdowns</a></li>
                        <li class=""><a href="#buttonGroups"><i class="icon-chevron-right"></i>Button groups</a></li>
                        <li class=""><a href="#buttonDropdowns"><i class="icon-chevron-right"></i>Button dropdowns</a></li>
                        <li class="active"><a href="#navs"><i class="icon-chevron-right"></i>Navs</a></li>
                        <li class=""><a href="#navbar"><i class="icon-chevron-right"></i>Navbar</a></li>
                        <li class=""><a href="#breadcrumbs"><i class="icon-chevron-right"></i>Breadcrumbs</a></li>
                        <li><a href="#" data-toggle="collapse" data-target="#demo">Pagination</a>  
                           <ul id="demo" class="collapse in nestednav">
                                <li class="active"><a href="#"><i class="icon-chevron-right"></i>Action</a></li>
                                <li><a href="#"><i class="icon-chevron-right"></i>Another action</a></li>
                            </ul>
                          </li>
                        <li><a href="#labels-badges"><i class="icon-chevron-right"></i>Labels and badges</a></li>
                        <li><a href="#typography"><i class="icon-chevron-right"></i>Typography</a></li>
                        <li><a href="#thumbnails"><i class="icon-chevron-right"></i>Thumbnails</a></li>
                        <li><a href="#alerts"><i class="icon-chevron-right"></i>Alerts</a></li>
                        <li><a href="#progress"><i class="icon-chevron-right"></i>Progress bars</a></li>
                        <li><a href="#media"><i class="icon-chevron-right"></i>Media object</a></li>
                        <li><a href="#misc"><i class="icon-chevron-right"></i>Misc</a></li>
                    </ul>
                </div>
                <div class="row-fluid">
                    <div class="sidebar">
                        <p>
                            side bar item1</p>
                    </div>
                </div>
                <div class="row-fluid">
                    <div class="sidebar">
                        <p>
                            side bar item2</p>
                    </div>
                </div>
            </div>
            <div class="span9" style="margin-left:0">
                <div class="row-fluid">
                    <ul class="breadcrumb">
                        <li><a href="#">Home</a> <span class="divider">/</span></li>
                        <li><a href="#">Library</a> <span class="divider">/</span></li>
                        <li class="active">Data</li>
                    </ul>
                </div>
                <div class="row-fluid">
               	<?php print render($page['content']); ?> 
                </div>
                <div class="row-fluid">
                    <p>
                        main content item2</p>
                </div>
            </div>
        </div>
        <div class="row-fluid">
            <p>
                test</p>
        </div>
          <div class="row-fluid">
            <p>
                test</p>
        </div>
          <div class="row-fluid">
            <p>
                test</p>
        </div>
        <hr>
        <footer>
            <p>
                © Company 2013</p>
        </footer>
    </div>

    