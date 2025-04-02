import os
import librosa
import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import Dataset, DataLoader, random_split
import torchvision.transforms as transforms

data_dir = r"C:\Users\domin\.cache\kagglehub\datasets\mohammedalkooheji\guitar-notes-dataset\versions\3\Guitar Dataset"
classes = [
    "A2",
    "A3",
    "A4",
    "Asharp2",
    "Asharp3",
    "Asharp4",
    "B2",
    "B3",
    "B4",
    "C3",
    "C4",
    "C5",
    "Csharp3",
    "Csharp4",
    "Csharp5",
    "D2",
    "D3",
    "D4",
    "D5",
    "Dsharp2",
    "Dsharp3",
    "Dsharp4",
    "Dsharp5",
    "E2",
    "E3",
    "E4",
    "E5",
    "F2",
    "F3",
    "F4",
    "F5",
    "Fsharp2",
    "Fsharp3",
    "Fsharp4",
    "Fsharp5",
    "G2",
    "G3",
    "G4",
    "G5",
    "Gsharp2",
    "Gsharp3",
    "Gsharp4",
    "Gsharp5",
]

target_shape = (128, 128)
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")


class GuitarNotesDataset(Dataset):
    def __init__(self, data_dir, classes, target_shape):
        self.data = []
        self.labels = []

        for i, class_name in enumerate(classes):
            class_dir = os.path.join(data_dir, class_name)
            for filename in os.listdir(class_dir):
                if filename.endswith(".wav"):
                    file_path = os.path.join(class_dir, filename)
                    audio_data, sample_rate = librosa.load(file_path, sr=44100)

                    # Normalize the audio data
                    audio_data = librosa.util.normalize(audio_data)

                    # Compute MFCCs instead of Mel Spectrogram
                    mfcc = librosa.feature.mfcc(
                        y=audio_data,
                        sr=sample_rate,
                        n_mfcc=100,  # n_mfcc sets the number of MFCC coefficients
                    )

                    # Normalize the MFCCs (optional but helps stabilize training)
                    mfcc = (mfcc - mfcc.mean()) / mfcc.std()

                    # Add a channel dimension for compatibility with PyTorch models
                    mfcc = np.expand_dims(mfcc, axis=0)
                    mfcc = torch.tensor(mfcc, dtype=torch.float32)

                    # Append to the dataset
                    self.data.append(mfcc)
                    self.labels.append(i)

        self.data = [
            torch.nn.functional.interpolate(
                d.unsqueeze(0), size=target_shape, mode="bilinear", align_corners=False
            ).squeeze(0)
            for d in self.data
        ]
        self.labels = torch.tensor(self.labels, dtype=torch.long)

    def __len__(self):
        return len(self.data)

    def __getitem__(self, idx):
        return self.data[idx], self.labels[idx]


dataset = GuitarNotesDataset(data_dir, classes, target_shape)
train_size = int(0.8 * len(dataset))
test_size = len(dataset) - train_size
train_dataset, test_dataset = random_split(dataset, [train_size, test_size])

train_loader = DataLoader(train_dataset, batch_size=16, shuffle=True)
test_loader = DataLoader(test_dataset, batch_size=16, shuffle=False)


class GuitarNotesModel(nn.Module):
    def __init__(self, num_classes):
        super(GuitarNotesModel, self).__init__()
        self.conv_layers = nn.Sequential(
            nn.Conv2d(1, 32, kernel_size=3),
            nn.ReLU(),
            nn.Conv2d(32, 64, kernel_size=3),
            nn.ReLU(),
            nn.Conv2d(64, 64, kernel_size=3),
            nn.ReLU(),
            nn.MaxPool2d(kernel_size=2),
            nn.Dropout(0.25),
        )

        with torch.no_grad():
            sample_input = torch.zeros(1, 1, *target_shape)
            conv_output_size = self.conv_layers(sample_input).view(-1).size(0)

        self.fc_layers = nn.Sequential(
            nn.Flatten(),
            nn.Linear(conv_output_size, 128),
            nn.ReLU(),
            nn.Dropout(0.5),
            nn.Linear(128, num_classes),
        )

    def forward(self, x):
        x = self.conv_layers(x)
        x = self.fc_layers(x)
        return x


model = GuitarNotesModel(num_classes=len(classes)).to(device)

criterion = nn.CrossEntropyLoss()
optimizer = optim.Adam(model.parameters(), lr=0.001)


def train_model(model, train_loader, criterion, optimizer, epochs=15):
    model.train()
    for epoch in range(epochs):
        running_loss = 0.0
        for inputs, labels in train_loader:
            inputs, labels = inputs.to(device), labels.to(device)
            optimizer.zero_grad()
            outputs = model(inputs)
            loss = criterion(outputs, labels)
            loss.backward()
            optimizer.step()
            running_loss += loss.item()
        print(f"Epoch {epoch + 1}/{epochs}, Loss: {running_loss / len(train_loader)}")


def test_model(model, test_loader):
    model.eval()
    correct = 0
    total = 0
    with torch.no_grad():
        for inputs, labels in test_loader:
            inputs, labels = inputs.to(device), labels.to(device)
            outputs = model(inputs)
            _, predicted = torch.max(outputs, 1)
            total += labels.size(0)
            correct += (predicted == labels).sum().item()
    print(f"Test Accuracy: {100 * correct / total}%")


train_model(model, train_loader, criterion, optimizer, epochs=25)
test_model(model, test_loader)
