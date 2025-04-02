fn main() {
    print!("{}", zoom(9));
}

fn get_opposite_square(sq: &str) -> &str {
    if sq == "□" {
        "■"
    } else {
        "□"
    }
}

fn zoom(n: i32) -> String {
    let squares = ("□", "■");
    let first_row = if n % 4 % 3 == 1 { squares.1 } else { squares.0 };

    let mut line = vec![first_row; n as usize];
    let mut lines: Vec<String> = vec![line.clone().into_iter().collect()];

    let mut left: usize = 0;
    let mut right: usize = (n - 1).try_into().unwrap();

    while left != right {
        left += 1;
        right -= 1;

        for i in left..=right {
            line[i] = get_opposite_square(line[i]);
        }
        lines.push(line.clone().into_iter().collect())
    }

    while left > 0 {
        left -= 1;
        lines.push(lines[left].clone());
    }

    lines.join("\n")
}
#[test]
fn basic_test_1() {
    assert_eq!(zoom(1), "■");
}

#[test]
fn basic_test_2() {
    assert_eq!(
        zoom(3),
        "\
□□□
□■□
□□□"
    );
}

#[test]
fn basic_test_3() {
    assert_eq!(
        zoom(5),
        "\
■■■■■
■□□□■
■□■□■
■□□□■
■■■■■"
    );
}

#[test]
fn basic_test_4() {
    assert_eq!(
        zoom(7),
        "\
□□□□□□□
□■■■■■□
□■□□□■□
□■□■□■□
□■□□□■□
□■■■■■□
□□□□□□□"
    );
}

#[test]
fn basic_test_5() {
    assert_eq!(
        zoom(9),
        "\
■■■■■■■■■
■□□□□□□□■
■□■■■■■□■
■□■□□□■□■
■□■□■□■□■
■□■□□□■□■
■□■■■■■□■
■□□□□□□□■
■■■■■■■■■"
    );
}
