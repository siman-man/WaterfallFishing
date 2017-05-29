#current = File.read("score/test.txt").split.map(&:to_f)
#current = File.read("score/final.txt").split.map(&:to_f)
current = File.read("master50.txt").split.map(&:to_f)
#current = File.read("sample_final.txt").split.map(&:to_f)
#current = File.read("divide_5_final.txt").split.map(&:to_f)
#now = File.read("prevent_adjust_wana.txt").split.map(&:to_f)
now = File.read("output").split.map(&:to_f)


result = current.zip(now).map do |c, n|
  if c == 0 && n == 0
    1.0
  elsif c > n
    2.0 - n / c
  elsif c < n
    c / n
  else
    1.0
  end
end

puts result.sum / current.size
