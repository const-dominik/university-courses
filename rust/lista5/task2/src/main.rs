fn main() {}

fn even_numbers(array: &Vec<i32>, number: usize) -> Vec<i32> {
    let mut ans = vec![];
    for x in array.into_iter().rev() {
        if ans.len() == number {
            break;
        }
        if x % 2 == 0 {
            ans.push(*x);
        }
    }

    ans.iter().rev().cloned().collect()
}

#[test]
fn test1() {
    assert_eq!(
        even_numbers(&vec!(1, 2, 3, 4, 5, 6, 7, 8, 9), 3),
        vec!(4, 6, 8)
    );
}

#[test]
fn test2() {
    assert_eq!(
        even_numbers(&vec!(-22, 5, 3, 11, 26, -6, -7, -8, -9, -8, 26), 2),
        vec!(-8, 26)
    );
}

#[test]
fn test3() {
    assert_eq!(
        even_numbers(&vec!(6, -25, 3, 7, 5, 5, 7, -3, 23), 1),
        vec!(6)
    );
}
#[test]
fn test4() {
    assert_eq!(even_numbers(&vec!(-25, 3, 7, 5, 5, 7, -3, 23), 0), vec!());
}
#[test]
fn test5() {
    assert_eq!(even_numbers(&vec!(6, 6, 6), 3), vec!(6, 6, 6));
}
