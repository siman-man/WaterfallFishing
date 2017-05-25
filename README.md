### 問題

Notes: Many elements of this problem may not resemble reality, have somewhat more randomized luck than usual,

この問題のほとんどはフィクションです。

and are made up for the sole purpose of producing a fun introductory marathon-style challenge.


### 説明

You are planning to setup fish traps to catch some fish while attending TCO,

あなたは TCO 参加中に 魚を捕まえるための罠を仕掛けることにしました。

and have been informed by some locals that the bottom of a large waterfall is a great place,

水深が深いところが良いポイントです。

since some fish are inevitably carried downstream and go over the falls. Being a bit of a data enthusiast,

なぜなら魚は水の流れによって下に落ちていくからです。

you theorize that by keeping track of counts of fish for several days ahead of time,

あなたは魚を捕まえることをここ見ました。

you may be able to get some sense of where fish are most likely to be caught.

(A description of how the river is modelled and fish locations are generated is given later in the problem statement below.)

川のモデリングや、魚の位置の生成については問題の後半に記されています。

Because you don't want to miss any of the TCO action, you will only setup your traps once, and will collect them after three days.

TCOのアクションを見逃したくないので、あなたは 1度罠を仕掛けると 3日後にしか回収できません


### 提出についての説明

You should produce a single method, placeTraps, which receives a single parameter String[] data.

あなたは `placeTraps` を実装してもらいます。

Each element of data represents the fish seen across the width (W) of the river for a single day.

Each character indicates the number of fish seen at that location, up to a maximum of 35.

各文字は魚の居場所を示しています。最大 35 匹です

(A = 10, Z = 35) It is possible that any location may actually see more than 35 total fish,

表現可能な魚の数が 35匹

but since your traps can't hold more than that, you stop counting after 35.

Your method should return an int[] indicating the location(s) where you would like to place traps to collect fish the next day. The length of the return should be between 1 and W. Each value should be between 0 and W-1, with no duplicates. Any invalid return will score no points for the test case.


### スコア

The raw score for a given test case will be fish-caught / total-traps. Note that each trap will catch a maximum of 35 fish,

各罠は最大 35匹 までしか捕まえることしかできません。

as you only collect once at the end of the three days.

あなたは 3日 に 1回しか回収することが出来ません。

The overall score across all test cases will be the sum of the relative scores for each test case.

Your relative score for a single test case is given by YOUR / BEST, where YOUR = your raw score on that case and BEST = the highest score anyone achieved on that test case.



### テストケースの生成

The width of the river, W, is chosen (uniformly) between 20 and 200.

川の広さは [20 - 200]

An upstream (empty) river length, L, is chosen (uniformly) between 5 and 100.

川の長さは [5 - 100] の間

A number of rocks is chosen (uniformly) between 5 and W*L/10.

岩の数は [5 - W*L/10] の間

The location of each rock is chosen (uniformly) as a random point (0..W-1, 0..L-1).

岩の出現位置はランダム

If any location is chosen where there is already a rock, or that is directly adjacent to another rock (up/down or left/right), a new location is chosen.

設置位置に既に岩が存在していた場合は、ランダムに近接のマスに移動します

A number of days of data are chosen between 4 and 20, which will be used for the data provided to your code.

Three additional day of data will be generated as the "ground truth" against which you will be tested.


The remaining steps are performed for each day's worth of data, including the three days against which your trap placement will be tested:
A number of fish is chosen (uniformly) between 5 and 100.
Two values, M and S, are chosen (uniformly) such that M is in the range 0..W-1 and S is in the range 2..W/4.
Each fish is generated with a starting position selected for a normal distribution with mean M and standard deviation S.
If any fish is generated outside the bounds of the river, a new location is chosen.
Each fish travels down the river. If at any point it meets a rock, it moves one unit to the left or right (at random, unless against the edge of the river).
This simulation continues for each fish until it goes over the waterfall and lands in it's final location (0..W-1).
Note that only the value of W is given (implied by string length) as part of the input to your code. The other data is used for generating the location of fish over the waterfall on each day, but is not explicitly provided.
