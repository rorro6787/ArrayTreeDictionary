# ArrayTreeDictionary
This is an implementation in c of a DataStruture that acts like a list in which you can insert, remove words and look if they are inside in logarithmic time. One visual example of the structure if we tried to store the words [lake last land lord my lastly lock lie layer lan], would be:
<p align="center">
   <img src="https://github.com/rorro6787/rorro6787/blob/main/Images/Sin%20t%C3%ADtulo.png" width="800" height="500" />
</p>
<hr style="height:2px;border-width:0;color:gray;background-color:gray">

## Atributtes of the DataStructure
The DataStructure itself is a pointer to an array of 26 nodes (1 for each letter in the alphabet) that will store 3 things: first of all, a boolean value that would clarify if the letter is being used and another one that would tell if that letter is the end of a word. A part of that each node would store a reference to another array of 26 nodes.
This way is really easy to decide if a word is stored or not in the structure. You only need n steps to decide if we already included that word (being n the length of the word).

