function calibrate() {
    // Get all the values from the form
    var oldXStep = document.getElementById("Xstep").value;
    var oldYStep = document.getElementById("Ystep").value;
    var oldZStep = document.getElementById("Zstep").value;
    var desiredXLength = document.getElementById("desiredXLength").value;
    var desiredYLength = document.getElementById("desiredYLength").value;
    var desiredZLength = document.getElementById("desiredZLength").value;
    var xLength = document.getElementById("xLength").value;
    var yLength = document.getElementById("yLength").value;
    var zLength = document.getElementById("zLength").value;

    var newXStep = (oldXStep*(desiredXLength/xLength)).toFixed(2);
    var newYStep = (oldYStep*(desiredYLength/yLength)).toFixed(2);
    var newZStep = (oldZStep*(desiredZLength/zLength)).toFixed(2);  

    // Apply new step values
    document.getElementById('resultX').textContent = "New x step: " + newXStep;
    document.getElementById('resultY').textContent = "New y step: " + newYStep;
    document.getElementById('resultZ').textContent = "New z step: " + newZStep;
    // Only show the new values if they are not non existent
    var m92Command = "M92"
    if (newXStep != "NaN"){
      m92Command += " x" + newXStep;
    }
    if (newYStep != "NaN"){
      m92Command += " y" + newYStep;
    }
    if (newZStep != "NaN"){
      m92Command += " z" + newZStep;
    }
    document.getElementById('resultText2').textContent = m92Command;
    // Show new values
    document.getElementById('resultX').style.display = "block";
    document.getElementById('resultY').style.display = "block";
    document.getElementById('resultZ').style.display = "block";
    document.getElementById('resultText').style.display = "block";
    document.getElementById('resultText2').style.display = "block";
    document.getElementById('copyButton').style.display = "block";
    // Show new values
    document.getElementById('resultX').classList.add('fade-in');
    document.getElementById('resultY').classList.add('fade-in');
    document.getElementById('resultZ').classList.add('fade-in');
    document.getElementById('resultText').classList.add('fade-in');
    document.getElementById('resultText2').classList.add('fade-in');

    // Scroll to bottom of page
    window.scrollTo(0, document.body.scrollHeight);

}

document.getElementById('copyButton').addEventListener('click', function() {
    var command = document.getElementById('resultText2').textContent;
    navigator.clipboard.writeText(command).then(function() {
      console.log('Copying to clipboard was successful!');
      document.getElementById('copyButton').textContent = "Copied!";
      document.getElementById('copyButton').classList.add('fade-in');
        setTimeout(function(){ 
            document.getElementById('copyButton').textContent = "Copy to clipboard";
            document.getElementById('copyButton').classList.remove('fade-in');
        }, 3000);
    }, function(err) {
      console.error('Could not copy text: ', err);
    });
  });