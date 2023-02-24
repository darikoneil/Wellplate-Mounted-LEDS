### Code and hardware design for characterizing sensor dynamics using wellplate-mounted LEDs
Lux Steinberg & Darik A. ONeil

Verbosity of feedback is controlled by conditional compilation.
Enable verbose feedback options removing the comment syntax "//":

```
# define (feedback option)
```

Script 1 is single trial format.      
Script 2 is for four trial sequences.     
Script 3 is for nine trial sequence.


TODO:
Test and push Script 4 which generates trial sequence from:
```
int trial_types
int trial_on_durations[trial_types] = {}
int trial_off_durations[trial_types] = {}
int trials_per_duration
int trial_sequence[trials_per_duration * trial_types * 2] = {}
```
