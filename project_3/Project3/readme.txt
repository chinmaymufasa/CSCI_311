test 1:
	The purpose of test one is to check when we have two paths of the same length but different number
	of points to stop at, we choose the option with the least amount of stops.

test 2:
	The purpose of test two is play around with fuel and how the vehicle has to take more stops as a results
	the only option available in terms of range pathing and not running out of fuel mid way.

test 3:
	The purpose of test three is to run the graph backwards from a higher index node to a midway node to see
	the need of possible alternative routes that take longer than usual. I used the test 2 graph to check.

test 4:
	The purpose of test four is to check for inability to reach a destination. Regardless of all nodes having
	have a charging station, we still can get to end point since all possible paths to source and destination
	even though it exists cannot be done due to lack of range.

test 5:
	The purpose of test 5 is to see whether the algortihm will take the only path available to it by charing up
	at a station on node 1 and returning back to node 0 and then to 5.
	Expected output:  19: 0 1 0 5
	My output: No path exists
	