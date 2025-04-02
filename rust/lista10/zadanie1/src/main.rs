use std::collections::HashSet;

struct Sudoku {
    data: Vec<Vec<u32>>,
}

impl Sudoku {
    fn is_valid_sudoku_square(&self) -> bool {
        let size = self.data.len();
        let sqrt_size = (size as f64).sqrt() as usize;

        for i in (0..size).step_by(sqrt_size) {
            for j in (0..size).step_by(sqrt_size) {
                if !self.is_valid_square(i, j, sqrt_size) {
                    return false;
                }
            }
        }
        true
    }

    fn is_valid_square(&self, row: usize, col: usize, sqrt_size: usize) -> bool {
        let mut seen = HashSet::new();
        for i in 0..sqrt_size {
            for j in 0..sqrt_size {
                let num = self.data[row + i][col + j];
                if num == 0 || num > (sqrt_size * sqrt_size) as u32 || !seen.insert(num) {
                    return false;
                }
            }
        }
        true
    }

    fn is_valid(&self) -> bool {
        let size = self.data.len();
        let sqrt_size = (size as f32).sqrt() as usize;
        let mut seen = HashSet::new();

        if size <= 0 || sqrt_size * sqrt_size != size {
            return false;
        }

        for i in 0..size {
            //checking rows
            for &num in &self.data[i] {
                let len = self.data[i].len() as u32;
                if num > len || num == 0 || !seen.insert(num) {
                    return false;
                }
            }

            seen.clear();
            //checking columns
            for row in &self.data {
                if row.is_empty() {
                    return false;
                }
                let num = row[i];
                let len = self.data[i].len() as u32;

                if num > len || num == 0 || !seen.insert(num) {
                    return false;
                }
            }
            seen.clear();
        }

        if !self.is_valid_sudoku_square() {
            return false;
        }

        true
    }
}

#[test]
fn good_sudoku1() {
    let good_sudoku_1 = Sudoku {
        data: vec![
            vec![7, 8, 4, 1, 5, 9, 3, 2, 6],
            vec![5, 3, 9, 6, 7, 2, 8, 4, 1],
            vec![6, 1, 2, 4, 3, 8, 7, 5, 9],
            vec![9, 2, 8, 7, 1, 5, 4, 6, 3],
            vec![3, 5, 7, 8, 4, 6, 1, 9, 2],
            vec![4, 6, 1, 9, 2, 3, 5, 8, 7],
            vec![8, 7, 6, 3, 9, 4, 2, 1, 5],
            vec![2, 4, 3, 5, 6, 1, 9, 7, 8],
            vec![1, 9, 5, 2, 8, 7, 6, 3, 4],
        ],
    };

    assert!(good_sudoku_1.is_valid());
}

#[test]
fn good_sudoku2() {
    let good_sudoku_2 = Sudoku {
        data: vec![
            vec![1, 4, 2, 3],
            vec![3, 2, 4, 1],
            vec![4, 1, 3, 2],
            vec![2, 3, 1, 4],
        ],
    };
    assert!(good_sudoku_2.is_valid());
}

#[test]
fn bad_sudoku1() {
    let bad_sudoku_1 = Sudoku {
        data: vec![
            vec![1, 2, 3, 4, 5, 6, 7, 8, 9],
            vec![1, 2, 3, 4, 5, 6, 7, 8, 9],
            vec![1, 2, 3, 4, 5, 6, 7, 8, 9],
            vec![1, 2, 3, 4, 5, 6, 7, 8, 9],
            vec![1, 2, 3, 4, 5, 6, 7, 8, 9],
            vec![1, 2, 3, 4, 5, 6, 7, 8, 9],
            vec![1, 2, 3, 4, 5, 6, 7, 8, 9],
            vec![1, 2, 3, 4, 5, 6, 7, 8, 9],
            vec![1, 2, 3, 4, 5, 6, 7, 8, 9],
        ],
    };
    assert!(!bad_sudoku_1.is_valid());
}

#[test]
fn bad_sudoku2() {
    let bad_sudoku_2 = Sudoku {
        data: vec![
            vec![1, 2, 3, 4, 5],
            vec![1, 2, 3, 4],
            vec![1, 2, 3, 4],
            vec![1],
        ],
    };
    assert!(!bad_sudoku_2.is_valid());
}

#[test]
fn bad_sudoku3() {
    let bad = Sudoku {
        data: vec![
            vec![1, 4, 2, 11],
            vec![3, 2, 4, 1],
            vec![4, 1, 3, 2],
            vec![2, 3, 1, 4],
        ],
    };
    assert!(!bad.is_valid());
}

fn main() {}
