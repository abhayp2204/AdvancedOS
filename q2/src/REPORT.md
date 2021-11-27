# REPORT FOR Q2

# General Idea
Each person is treated as a thread, and each seat is treated as a lock. This way, a person will not have to wait for another
person to start his booking, unless they try to book the same seat. We also have threads for each goal that will interact
with the persons by causing them to get enraged.

# Person Thread
We have an array of group structures each of which has an array of person structures. Each person can be identified by a pair of indices i and j.  
For example, if (i, j) is (1, 2), we are referring to the 3rd person from the 2nd group.
Similarly (0, 1) refers to the second person from the first group.  

## reach()
The person thread calls `reach()` which sleeps until the person has arrived, and then prints that the person has reached the stadium.

We then check if a seat is available for this person which depends on whether the zones that this person is eligible for are full or not.
`seatZone` is the variable that stores the zone that the person will be seated in.  

## probHome()
This function determines the zone for a person supporting HOME team. Such a person can be seated in HOME or NEUTRAL zones.
If there are 6 HOME seats and 3 NEUTRAL seats are available, he will have a 6/9 probability of being seated in HOME and a 3/9 probabilty of being seated in NEUTRAL. This is in line with the fact that he does not have a preference for any zone.

## probNeutral()
This is the same as `probHome` but the person can be seated in any zone.

## probAway()
This is the same as `probHome` but the person can be seated only in AWAY zone so it just returns AWAY.

By the end of the switch block, we have the person's `seatZone`. If a seat is available in that zone, c will be positive.
We declare `timeOut` to be 0, (`timeOut` being 1 indicates that the patience time ran out) and break. Then we lock this seat and call `seat()`.

If a seat is not available, c will be negative. We call `noseat()` to print that the person could not find a seat. We then wait for a `signal`. This signal is sent whenever another person leaves the stadium because this may mean that a seat is now available. The whole seat allocation process happens again.

## patience()
If no seat is allocated for a person within the `patience time`, they exit the loop and `patience()` is called since `timeOut` is set to 1.

## dinner()
Whenever a person leaves, `dinner()` is called to check if all members of the group are waiting, in which case, the group leaves for dinner.

# Seat

## seatAvailable()
This function finds the index of the first available seat given the zone. It returns -1 if no seat is available.

## seat()
Prints that the person has got a seat in a certain zone. This person then sleeps for `spectating time`. During this time, if the person already left due to getting enraged, his status is set to `WAITING` and this function returns. Otherwise the `spectating time` gets over and we print that the person waited for `X` seconds and is leaving.

# Goal Thread
Each goal thread sleeps for `Goal[i].GoalTime` and proceeds. There is a `Prob()` function to simulate probabilty. If the goal is scored by `HOME` team, we call `leaveAWAY()` to check if someone from `AWAY` team gets enraged and leaves and vice versa for `AWAY` team. Otherwise we print that the goal missed.