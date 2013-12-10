/**
 * @file
 * bootstrap.js
 *
 * Provides general enhancements and fixes to Bootstrap's JS files.
 */

var Drupal = Drupal || {};

(function($, Drupal){
 
  Drupal.behaviors.bootstrapcc = {
    attach: function(context) {

    	// IE10 viewport hack for Surface/desktop Windows 8 bug
        //
        // See Getting Started docs for more information
        if (navigator.userAgent.match(/IEMobile\/10\.0/)) {
          var msViewportStyle = document.createElement("style");
          msViewportStyle.appendChild(
            document.createTextNode(
              "@-ms-viewport{width:auto!important}"
            )
          );
          document.getElementsByTagName("head")[0].
            appendChild(msViewportStyle);
        }


        var $window = $(window)
        var $body   = $(document.body)

        var navHeight =
        $('.navbar').outerHeight(true)-$('#toolbar').outerHeight(true) + 10

        $body.scrollspy({
          target: '.cp-sidebar-menu',
          offset: navHeight
        })

        $window.on('load', function () {
          $body.scrollspy('refresh')
        })

        $('.cp-docs-container [href=#]').click(function (e) {
          e.preventDefault()
        })

        // back to top
        setTimeout(function () {
          var $sideBar = $('.cp-sidebar-menu')

          $sideBar.affix({
            offset: {
              top: function () {
                var offsetTop      = $sideBar.offset().top
                var sideBarMargin  = parseInt($sideBar.children(0).css('margin-top'), 10)
                var navOuterHeight = $('.navbar').height()-$('#toolbar').height()

                return (this.top = offsetTop - navOuterHeight - sideBarMargin)
              }
            , bottom: function () {
                return (this.bottom = $('.cp-footer').outerHeight(true))
              }
            }
          })
        }, 100)

       

        /**
        // tooltip demo
        $('.tooltip-demo').tooltip({
          selector: "[data-toggle=tooltip]",
          container: "body"
        })

        $('.tooltip-test').tooltip()
        $('.popover-test').popover()

        $('.bs-docs-navbar').tooltip({
          selector: "a[data-toggle=tooltip]",
          container: ".bs-docs-navbar .nav"
        })

        // popover demo
        $("[data-toggle=popover]")
          .popover()

        // button state demo
        $('#fat-btn')
          .click(function () {
            var btn = $(this)
            btn.button('loading')
            setTimeout(function () {
              btn.button('reset')
            }, 3000)
          })
    	
    	**/
    }
  };

})(jQuery, Drupal);
