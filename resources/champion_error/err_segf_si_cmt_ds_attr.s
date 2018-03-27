.name #"zork"

.comment "I'M ALIIIIVE"
   
l2:		
boo: 	sti r1, %:live, %1
		and r1, %0, r1
  
live:	live, %1
		zjmp %:boo
	
#segfault aussi avec:
#  .name
#  [ligne vide]
#  .comment "cmt"
#
