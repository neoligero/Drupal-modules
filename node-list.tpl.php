<?php
	if(count($var) > 1){
		echo "<table>";
		foreach ($var as $node) {
			echo "<tr>";
				echo "<td>".$node['type']."</td>";
				echo "<td>".$node['title']."</td>";
			echo "</tr>";
		}
		echo '</table>';
	}
	else{
		echo $var[0];
	}
?>