const observer = new IntersectionObserver(entries => {
  entries.forEach(entry => {
    const square = entry.target.querySelector('.a');

    if (entry.isIntersecting) {
      square.classList.add('animation-bigger');
	  return; // if we added the class, exit the function
    }

    // We're not intersecting, so remove the class!
    square.classList.remove('animation-bigger');
  });
});
// Tell the observer which elements to track
observer.observe(document.querySelector('#testimonials'));
