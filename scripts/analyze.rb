class Analyze
  TSV_LABEL = ['seed', 'score', 'time'].join("\t")

  def initialize
    data_list = parse
    time_stamp = Time.now.strftime("%m%d-%H%m%S")

    @record = File.open(File.expand_path("data/record-#{time_stamp}.tsv", Dir::pwd), 'w')
    result = []

    begin
      @record.puts(TSV_LABEL)

      sum_score = 0.0
      seeds = []

      data_list.each do |data|
        data = clean_data(data)
        result << data

        seeds << data[:seed]
        puts data[1]
        if data[1] == -1.0
          sum_score += Float::INFINITY
        else
          sum_score += data[:score]
        end
        @record.puts(data.values.join("\t"))
      end

      #p seeds
      puts "#{sum_score / data_list.size}"
    ensure
      @record&.close
    end

    result.group_by { |d| [d[:width] - 1, 20].max / 10 }.sort.each do |id, datas|
      sum = 0

      datas.each do |d|
        sum += d[:score]
      end

      puts [sum / datas.size]
      #puts [id, sum / datas.size].join(' ')
    end
  end 

  def clean_data(data)
    seed = data['seed']&.to_i
    score = data['score']&.to_f
    /(?<minute>\d+)m(?<second>(\d|\.)+)s/ =~ data['user']
    time = minute.to_f * 60 + second.to_f
    width = data['width']&.to_i

    {seed: seed, score: score, time: time, width: width}
  end

  def parse
    filepath = File.expand_path('result.txt', Dir::pwd)
    data_list = []
    data = {}

    File.open(filepath, 'r') do |file|
      file.each_line do |line|
        line = clean_line(line)

        if line =~ /begin/
          data = {}
        elsif line =~ /!end!/
          data_list << data.dup
        else
          if validate(line)
            h = line2hash(line)
            data.merge!(h)
          end
        end
      end
    end

    data_list
  end

  def line2hash(line)
    Hash[*line.split]
  end

  def clean_line(line)
    line.chomp.downcase.delete('=')
  end

  def validate(line)
    line =~ /^(score|seed|user|width)/
  end
end

Analyze.new
