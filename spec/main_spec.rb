describe 'database' do
  def run_script(commands)
    raw_output = nil
    IO.popen("./build/db", "r+") do |pipe|
      commands.each do |command|
        pipe.puts command
      end

      pipe.close_write

      # Read entire output
      raw_output = pipe.gets(nil)
    end
    raw_output.split("\n")
  end

  it 'inserts and retreives a row' do
    result = run_script([
      "insert 1 user1 person1@example.com",
      "select",
      ".exit",
    ])
    expect(result).to match_array([
      "sdb > Executed 'insert 1 user1 person1@example.com'.",
      "sdb > 1, user1, person1@example.com",
      "Executed 'select'.",
      "sdb > ",
    ])
  end

  it 'prints error message when table is full' do
    script = (1..1401).map do |i|
      "insert #{i} user#{i} person#{i}@example.com"
    end
    script << ".exit"
    result = run_script(script)
    expect(result[-2]).to eq('sdb > Error: Table full.')
  end
end