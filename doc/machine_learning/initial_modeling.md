# Overview

As a person who enjoys inhabiting a space at a comfortable temperature I want a system that keeps the temperature where I want it at minimal cost. :)

Building an intelligent HVAC system can be modeled as a 2 variable optimization problem seeking to simultationously 1) minimize energy usage and 2) maximizing the desirability of the temperature. Genetic algorithms (a machine learning technique) can be used to find sequences of HVAC events (like turning the furnace, AC, or fan on or off) that perform well at this optimization under different circumstances (like when the external forecasted temperature is rising, static, or decreasing and at different temperature ranges).  The historical perfomance of each HVAC sequence (a set of moves to play this optimization game) can be summarized and ordered according to a utility function. Genetic "mates" for future recommended HVAC sequences can be selected by chosing sequences at the top of the list that maximize the utilizty function. Variation/mutation can be introduced by choosing elements other than the top two (the two best). A Pandora-like interface that would allow users to "thumbs down (crapy temp)" or "thumbs down (too expensive)" previous HVAC sequences to weight their preferences.

## Settable Global Variables
* HVAC Action Cycle Time  1 minute): The minimum amount of time an HVAC action can persist for.
* Learning period (3 hours): The number of hours to look forward and the number of ours to roll up utility function performance
* Carbon equivilent power consumption for each HVAC action type:
  * Furnace (X watts/hr ??)
  * AC (Y watts/hr ??)
  * Fan (Z watts/hr ??)
* Active time period vs inactive time period, default
  * 9pm-5am: Inactive (where minimizing cost gets more weight)
  * 5am-9pm: Active   (where maximizing temp desirability gets more weight)

## Periodic Input Variables

* Current inside temp
* Current desired inside temp
* Current forecasted temperature

## Derived Input Variables (for discretization)
* Projected temperature pattern
  * -1: decreasing
  * 0: static
  * 1: increasing

* Temperature range (F)
  * 0: below -10
  * 1: -9 to 10
  * 2: 11 to 30
  * 3: 31 to 50
  * 4: 51 to 70
  * 5: 70 to 90
  * 6: above 90

## Utility/Optimization Functions

* Desirability function (Fc): The integral of the HVAC Action Cycle Time units over a the Learning Period of the difference between the desired and actual temperature.
* Power consumption function (Fd): The integral of power usage over the Learning Period.
* Utility function (Fu): 1 - [ Fc + Fd ]

Possible additions:

* Fd could be weighted by "thumbs downs" user actions
* Overall utility function (Fu) could be weight Fc or Fd based on temperature range, active/inactive state, or forecasted external temperature change.

## Periodic Output Variables

* HVAC Action: Turn the furance, AC, or fan on or off
* Recommended Next HVAC Sequence: What sequence of HVAC actions should be taken for the next learning period>
* Historical HVAC Sequences: All previous HVAC sequences and their utility function score.

## Simplifying Assumptions (for the Hackathon)

* HVAC Actions are binary (turn on or off). In the real world you might want to specify "% on" or some continuous var.
* No motion sensor (like the NEST). Not relevant our the CoCo situation.
* The system operates can easily be turned off and simply runs the the regular therostat circuit.

## Machine learning algorithms considered

In order of preference and perceived potential applicability
* Genetic algorithms
* Markov models
* Bayesian learning
* Decision trees
* Neural networks
* Support vector machines

## Spark Core State Firmware state

The core exposes (via Spark.variable) 
  * current_temp:
  * current_hvac_action: 
    * heat_on
    * ac_on
    * fan_on
    * off
  * next_hvac_action:
  * last_hvac_action:
  * last_hvac_action_unix_timestamp:
  * current_time_offset_from_last_timestamp:

