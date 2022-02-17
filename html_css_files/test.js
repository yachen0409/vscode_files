// hello world
alert("Hello World from Javascript!")
// if statement
var meat = false;
if(meat){
    document.write("you like meat");
    document.write("<br>");
}
else{
    document.write("you don't like it!!!!");
    document.write("<br>");
}

// else-if statement
var age = 55;
if(age > 30){
    document.write("You are over 30!");
}
else if(age > 10){
    document.write("You are over 10!");
}
else{
    document.write("You are a baby......");
}
document.write("<br>");

//for loop and get tag's length
var link = document.getElementsByTagName("a");
for (i = 0; i < link.length; ++i){

    console.log("Looped link No" + i);
    link[i].className = "myclass";
}
document.write("All links are looped!!!");

//function practice
function getaverage (a, b){
    var ave = (a+b) / 2;
    console.log(ave);
}

getaverage(5, 10);