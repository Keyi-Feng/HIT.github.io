window.onload = function(){
    var button = document.querySelectorAll(".left-nav .left-nav-goods");
    for( var i=0 ; i<button.length ; i++ ){
        button[i].onclick = function(){
            for(var j=0 ; j<button.length ; j++ ){
                if(getComputedStyle(button[j],null).backgroundColor == "rgb(255, 255, 255)" ){
                    button[j].style.color = "#ffffff";
                    button[j].style.backgroundColor = "transparent";
                    button[j].nextElementSibling.style.width = "0px";
                    button[j].nextElementSibling.style.boxShadow = "none";
                    this.nextElementSibling.style.overflow = "hidden";
                }
            }
            this.nextElementSibling.style.width = "992px";
            this.nextElementSibling.style.boxShadow = "10px 0 10px rgba(0, 0, 0, .1)";
            this.nextElementSibling.style.border = "1px solid #E0E0E0";
            this.nextElementSibling.style.overflow = "auto";
            this.style.color = "black";
            this.style.backgroundColor = "#ffffff";
        }
    }
}