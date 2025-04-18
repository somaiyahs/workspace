// Fuction to generate a random color 
function getRandomColor(){
    const letters = "0123456789ABCDEF";
    let color = "#";
    for (let i=0; i<6;i++){
        color+=letters[Math.floor(Math.random()*16)];
    }
    return color; 
}

//Function to change the background color and update the text
function changeBackgroundColor(){
    //get a random color
    const newColor = getRandomColor();

    //change the background color of the body
    document.body.style.backgroundColor = newColor;

    // update the paragraph to show the new color
    document.getElementById("currentColor").textContent = "Current Background Color: " + newColor;
}

// Attach the changeBackgroundColor function to the button click event 
document.getElementById("changeColorButton").addEventListener("click", changeBackgroundColor);