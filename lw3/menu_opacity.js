document.addEventListener("click", function (e) {
    let m = document.getElementById('menu');
    if (e.target.id != 'menu_trigger' && e.target.id != 'menu') {
        m.style.opacity = 0;
    } else if (e.target.id == 'menu_trigger') {
        m.style.opacity = (m.style.opacity != 1) ? 1 : 0;
    }
});