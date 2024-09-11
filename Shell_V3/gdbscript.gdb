define printMember
	
	print Piped_Command->Command
	set $i = 0
	while $i < 10
		print Piped_Command->Arguments[$i]
		$i = $i + 1
	set variable i = 0
	while $i < 10
		print Piped_Command->Options[$i]
		$i = $i + 1
	set $i = 0
	while $i < 10
		print Piped_Command->OutputRedir[$i]
		$i = $i + 1
	set $i = 0
	while $i < 10
		print Piped_Command->OutputErrorRedir[$i]
		$i = $i + 1
	set $i = 0
	while $i < 10
		print Piped_Command->InputRedir[$i]
		$i = $i + 1
	print Piped_Command->ArgNum
	print Piped_Command->OptnNum




