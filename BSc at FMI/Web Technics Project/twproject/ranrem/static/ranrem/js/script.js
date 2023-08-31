// menu

$(function() {
    menu = $('nav ul');

    $('#toggle-btn').on('click', function(e) {
        e.preventDefault();
        menu.slideToggle();
    });

    $(window).resize(function() {
        var w = $(this).width();
        if(w > 580 && menu.is(':hidden')) {
            menu.removeAttr('style');
        }
    });

    $('nav li').on('click', function(e) {
        var w = $(window).width();
        if(w < 580) {
            menu.slideToggle();
        }
    });
    $('.open-menu').height($(window).height());
});

// smooth scrolling

$('a[href*="#"]')
.not('[href="#"]')
.not('[href="#0"]')
    .click(function(event) {
        if (
            location.pathname.replace(/^\//, '') == this.pathname.replace(/^\//, '')
            &&
            location.hostname == this.hostname
        ) {
            var target = $(this.hash);
            target = target.length ? target : $('[name=' + this.hash.slice(1) + ']');
            if (target.length) {
                event.preventDefault();
                $('html, body').animate({
                    scrollTop: target.offset().top
                }, 1000, function() {
                    var $target = $(target);
                    $target.focus();
                    if($target.is(":focus")) {
                        return false;
                    } else {
                        $target.attr('tabindex', '-1');
                        $target.focus();
                    };
                });
            }
        }
    });

// view more with ajax

var csrftoken = Cookies.get('csrftoken');

function csrfSafeMethod(method) {
    return (/^(GET|HEAD|OPTIONS|TRACE)$/.test(method));
}

$.ajaxSetup({
    beforeSend: function(xhr, settings) {
        if (!csrfSafeMethod(settings.type) && !this.crossDomain) {
            xhr.setRequestHeader("X-CSRFToken", csrftoken);
        }
    }
});

$('#show_more')
    .click(function(event){
        event.preventDefault();
        $('#results_ajax').fadeIn("slow");
        setTimeout(function() {
            $.ajax({
                url: "showmore/",
                type: "POST",
                dataType: "html",
                success: function(msg) {
                    j = JSON.parse(msg);
                    $('<p id="ajax-content">'+j['load']+'</p>').insertBefore('#show_more');
                    $('#show_more').css("display", "none");
                    $('#show_less').css("display", "block")
                },
                error: function(xhr, status, error) {
                    console.log(status);
                    console.log(error);
                }
            });
        }, 0);
    });

$('#show_less')
    .click(function(event){
        event.preventDefault();
        $('#ajax-content').remove();
        $('#show_less').css("display", "none");
        $('#show_more').css("display", "block")
    });