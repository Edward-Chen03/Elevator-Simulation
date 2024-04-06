document.addEventListener('DOMContentLoaded', function() {
    fetch('Elevator.cpp')
        .then(response => response.text())
        .then(data => {
            document.getElementById('display').textContent = data;
        })
        .catch(error => console.error('Error: ', error));
});
