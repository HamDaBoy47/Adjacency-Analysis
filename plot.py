import random
import pandas as pd
import matplotlib.pyplot as plt

# read csv file into a dataframe
df = pd.read_csv("RectDetails.csv")

# print(df.keys())

# create a figure and axis object
fig, ax = plt.subplots()

# iterate over each row in the dataframe
for index, row in df.iterrows():
    x = row["BLx"]
    y = row["BLy"]
    width = row["width"]
    height = row["height"]
    rect_id = row["id"]
    color = (random.random(), random.random(), random.random())

    # create a rectangle patch
    rect = plt.Rectangle(
        (x, y), width, height, linewidth=0.2, edgecolor="black", facecolor=color
    )

    # add the patch to the axis
    ax.add_patch(rect)

    # add the id as text to the center of the rectangle
    plt.text(
        x + width / 2,
        y + height / 2,
        str(rect_id),
        horizontalalignment="center",
        verticalalignment="center",
        color="black",
    )

# set axis limits
ax.set_xlim(df["BLx"].min() - 1, df["BLx"].max() + df["width"].max() + 1)
ax.set_ylim(df["BLy"].min() - 1, df["BLy"].max() + df["height"].max() + 1)

# set title
plt.title("Randomly colored rectangles")

# save the plot as a pdf
plt.savefig("plot.pdf", format="pdf")

# show the plot
plt.show()
