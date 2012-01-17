<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">
<head>
	<?php print $head; ?>
    <title><?php print $head_title; ?></title>
    <?php print $styles; ?>
    <?php if ($right){} ?>
    <?php if ($left){} ?>
    <?php print $scripts; ?>
</head>
<body<?php print phptemplate_body_class($left, $right); ?>>
    <div id="doc2" class="yui-t2">
        <div id="hd"><a name="top"></a>
            <div id="metanav">
				<p>Site-wide links</p>
				<ul>
					<li id="metaskip"><a href="#pagecontent" title="Skip to content">Skip to content</a></li>
					<li id="metarithome"><a href="http://www.rit.edu/" title="RIT Home"><span id="metarithometext">RIT Home</span><span id="metaritlogo"></span></a></li>
					<li id="metaritdirectories"><a href="http://www.rit.edu/directories/">Directories</a></li>
					<li id="metaritsearch"><a href="http://www.rit.edu/search/">Search RIT</a>
                        <div id="metaritsearchdiv">
                            <form id="metasearchform" method="get" action="http://www.rit.edu/search/">
                                <div>
                                    <input id="metaritsearchbox" class="faded" name="q" type="text" value="Search RIT" maxlength="250" alt="Search box" onfocus="focusSearch(this)" 
                                        onblur="blurSearch(this)" />
                                    <button title="Submit Search">Search</button>
                                </div>
                            </form>
                        </div>
					</li>
				</ul>
				<script type="text/javascript">
				function focusSearch(formfield){ if (formfield.defaultValue==formfield.value) formfield.value = ""; formfield.className = ""; }
				function blurSearch(formfield){ if (formfield.value==""){ formfield.value = formfield.defaultValue; formfield.className = "faded";} }
				</script> 
            </div>
            <?php print $breadcrumb; ?>
            <div id="banner"><div id="banner-image"> 
                <div id="logo-floater">
                    <?php
                    // Prepare header
                    $site_fields = array();
                    if ($site_name) {
                        $site_fields[] = check_plain($site_name);
                    }
                    if ($site_slogan) {
                        $site_fields[] = check_plain($site_slogan);
                    }
                    $site_title = implode(' ', $site_fields);
                    if ($site_fields) {
                        $site_fields[0] = '<span>'. $site_fields[0] .'</span>';
                    }
                    $site_html = implode(' ', $site_fields);
    
                    if ($logo || $site_title) {
                        print '<h1 id="sitetitle"><a href="'. check_url($front_page) .'">';
                        if ($logo) {
                            print '<img src="'. check_url($logo) .'" alt="site logo" id="logo" />';
                        }
                        print $site_html .'</a></h1>';
                    }
                    ?>
                </div>
			</div></div>
            <?php print $header; ?>
        </div>
        <div id="bd">
            <div id="sitenav1"><!-- HORIZONTAL Navigation --> </div>
            <div id="yui-main">
                <div class="yui-b">
                    <div class="grid1">
                        <div class="g1unit first">
							<?php //if ($mission): print '<div id="mission">'. $mission .'</div>'; endif; ?>
							<?php if ($tabs): print '<div id="tabs-wrapper" class="clear-block">'; endif; ?>
							<?php if ($title): print '<h1'. ($tabs ? ' class="with-tabs"' : '') .'>'. $title .'</h1>'; endif; ?>
                            
							<?php if ($tabs): print '<ul class="tabs primary">'. $tabs .'</ul></div>'; endif; ?>
							<?php if ($tabs2): print '<ul class="tabs secondary">'. $tabs2 .'</ul>'; endif; ?>
                            
							<?php if ($show_messages && $messages): print $messages; endif; ?>
							<?php print $help; ?>
							<?php print $content; ?>
                            
                        </div>
                        <div class="g1unit second"><!-- Grid1 second column -->
            	            <?php if ($right): ?>
							<?php print $right; ?>
							<?php endif; ?>
                        </div>
                    </div>
                </div>
            </div>
            <div class="yui-b"><!-- Static width side column -->
				<?php if ($left): ?>
				<?php print $left; ?>
				<?php endif; ?>
            </div>
        </div>
        <div id="ft">
            <?php print $footer_message . $footer; ?>
        </div>
    </div>
    <script type="text/javascript">var gaJsHost = (("https:" == document.location.protocol) ? "https://ssl." : "http://www.");document.write(unescape("%3Cscript src='" + gaJsHost +  "google-analytics.com/ga.js' type='text/javascript'%3E%3C/script%3E"));</script>
    <script type="text/javascript">try {var pageTracker = _gat._getTracker("UA-10681416-1");pageTracker._trackPageview();} catch(err) {}</script>
    <?php print $closure; ?>
</body>
</html>
