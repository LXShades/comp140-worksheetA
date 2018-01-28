# Improved algorithm rationale
At first, I wanted to find an algorithm that guaranteed it was logically possible to find the exact word within the three lives you have.  

This was too challenging for me, so in the end I settled for an algorithm that picks the most similar words possible to the secret word. This meant sorting them in descending order of similarity. The surprising side-effect was that the game became easier to win anyway, as it now visualises a noticeable trail of words based on the commonness of letters, and is thus very often easy to win if you know what it's doing. It's still not guaranteed, though.

# Improved algorithm psuedocode (rough version)
```
array options = array(secret_word)     # word options, beginning with the secret word
array word_list = get_dictionary()     # list of words candidates to add to the options

while options.size() < max_number_of_options:
    # Add the next word with the highest similarity
    variable highest_similarity = -1      # similarity factor of the most similar word found so far--initialised to -1, so that we'll provide words with 0 similarity if absolutely nothing better is found.
    variable highest_similarity_word = "" # actual text of the most similar word so far

    # Iterate through every word
    # (Todo: start from a random index, so that candidates with the same similarity score are effectively randomly picked)
    foreach word in word_list:
        if word in options:
            continue # Skip words that are already in the options list
        endif

        # Check if this word's similarity is higher than the rest we've looked through
        current_similarity = get_similarity(word, secret_word)
        if current_similarity > highest_similarity:
            # Replace the highest similarity word with this new one and update the similarity score
            highest_similarity = current_similarity
            highest_similarity_word = word
        endif
    endfor

    # Add the new word candidate to the options list
    options.insert(highest_similarity_word)
endwhile
```

# Further considerations
- What happens if the word list is empty?  
 - The word "" is added repeatedly until the word count is reached.  
- The Psuedocode differs slightly from the final version--the final version takes the most similar word's index instead of its text. As the index is initialised to 0, this means that the first word in the word list will be added if no other candidates are found. This isn't game-breaking, but would be an odd-looking bug  
- The final version also starts from a random point in the list as suggested in the todo.