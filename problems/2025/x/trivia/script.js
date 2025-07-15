const msgOne = document.getElementById('feedback-msg-one');
const options = document.querySelectorAll('.options');
const correctAnswer = 'Blue Whale';

options.forEach((element) => (
  element.addEventListener('click', () => {
    if (element.textContent === correctAnswer) {
      element.classList.toggle('correct');
      msgOne.textContent = 'Correct';
    } else {
      element.classList.toggle('incorrect');
      msgOne.textContent = 'Incorrect';
    }
  })
));

const msgTwo = document.getElementById('feedback-msg-two');
const inputElement = document.getElementById('input-answer');
const buttonElement = document.getElementById('check-answer');

const rightAnswer = 'france';
buttonElement.addEventListener('click', (event) => {
  if (inputElement.value.toLowerCase() === rightAnswer) {
    inputElement.style.color = 'green';
    msgTwo.textContent = 'Correct';
  } else {
    inputElement.style.color = 'red';
    msgTwo.textContent = 'Incorrect';
  }
});
