WIDTH = 100
class WaterfallFising
  def initialize
    @field = []
    @width = WIDTH
    @height = 20
    @rocks = Array.new(@height) { Array.new(@width) }
  end

  def can_place_rock?(y, x)
    return false if @rocks[y][x]
  end

  def gaussian()
    sum = 0.0
    12.times{ sum += rand() }
    sum - 6
  end

  def get_daily_fish
    num_fish = 5 + rand(96)
    mean = rand(@width)
    st_dev = 2 + rand(@width / 4 - 1)
    ret = Array.new(@width, 0)

    while num_fish > 0
      x = (gaussian() * st_dev + mean).round
      next if x < 0 || x > @width - 1

      ret[x] = [ret[x]+1, 35].min

      num_fish -= 1
    end

    ret
  end
end

sum = Array.new(WIDTH, 0)

1000.times do
  wf = WaterfallFising.new
  ret = wf.get_daily_fish

  ret.each_with_index do |num, index|
    sum[index] += num
  end
end

p sum
