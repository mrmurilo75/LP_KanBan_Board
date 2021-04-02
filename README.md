# LP_KanBan_Board
Repo for Project 01 for the Programming Laboratory class (2020/2021 UPorto FCUP)

# TODO 
	fix issue with writing author:
		create new function write author
		check if auhtor already exists by reading from file and comparing:
			one way todo this is to check each letter with the last of the new author
			if the letter is equal you go back in the file the amount of the new author size and check if it match
			if it matches, goes 1 letter bf the first letter and return that position with ftell
			otherwise, write to the end of file and return the pos (this can be done just what is current in use: 'return writeText(fauthor, ...'


	fix viewByAuthor :
		it nedds to be updated to show new card field *id*
	
	implement all othher view's
		(use view by author as exemple)
