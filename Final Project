import streamlit as st
import pandas as pd
import numpy as np
import pydeck as pdk
import plotly.express as px

DATA_URL = ("Desktop/PythonJP/MVCollisionsDataDictcdionary_20190813_ERD.xlsx")

DATA_URL2 = ("494724_1234657_compressed_time_series_covid_19_confirmed_US.csv/time_series_covid_19_confirmed_US.csv")

DATA_URL3 = ("Desktop/PythonJP/494724_1234657_compressed_time_series_covid_19_confirmed_US.csv/time_series_covid_19_confirmed_US.csv")

st.title("Corona Virus Cases in the United States")
st.markdown("This application is a streamlit dashboard to analyze confirmed COVID-19 Cases in the United States 👑🦠")

@st.cache(persist = True)
def load_data(nrows):
    data = pd.read_csv(DATA_URL2, nrows = nrows)
    data['Prevalent_Cases'] = data['6/10/20'] - data['5/27/20']
    data.dropna(subset = ["Lat","Long_"], inplace = True)
    data.rename(columns={'Lat':'latitude'}, inplace=True)
    data.rename(columns={'Long_':'longitude'}, inplace=True)
    data = data.iloc[:,6:]
    return data

data = load_data(3261) #Remember to change
original_data = data
#original_data = original_data.rename(columnes = {'6/10/20' : "Total_Cases"})

st.header("Which Areas of the US are at Highest Risk for Corona Virus Cases?")
Number_of_Cases = st.slider("Number of Prevailing Cases",0,10000)
st.map(data.query("Prevalent_Cases >= @Number_of_Cases")[["latitude","longitude"]].dropna(how = "any"))

st.header("How many cases per State/Province?")
state = st.selectbox("State/Province", data['Province_State'].unique())
data = data[data['Province_State'] == state]

st.markdown("Covid-19 Cases in %s" % (state))

midpoint = (np.average(data['latitude']), np.average(data['longitude']))

st.write(pdk.Deck(
    
    map_style= "mapbox://styles/mapbox/light-v9",
    initial_view_state = {
        "latitude": midpoint[0],
        "longitude": midpoint[1],
        "zoom": 11,
        "pitch": 50,
    },
    layers=[
        pdk.Layer(
        "HexagonLayer",
        data = data[['Prevalent_Cases', 'latitude','longitude']],
        get_position=['longitude','latitude'],
        radius=30000,
        auto_highlight=True,
        extruded=True,
        pickable=True,
        elevation_scale=50,
        elevation_range=[0, 1000],
        ),
    ],
))


st.header("Covid-19 Cases Over Time in %s" % state)
Day_1 = st.selectbox("Start Day", list(data.iloc[:,11:-1].columns))
Day_2 = st.selectbox("End Day", list(data.iloc[:,11:-1].columns))
filtered = data.loc[:,Day_1:Day_2]
filtered_sum = filtered.sum(axis=0).to_frame()
filtered_sum.index.name = 'Date'
filtered_sum.reset_index(inplace=True)
filtered_sum.columns.values[1] = "Number of Cases"
st.subheader("Breakdown of Cases bewteen %s and %s" % (Day_1, Day_2))
fig = px.line(filtered_sum, x ='Date', y = 'Number of Cases', hover_data = ['Date','Number of Cases'], height = 400)
st.write(fig)

st.header("Top 5 States with the Most Covid-19 Cases")
#select = st.selectbox('County', ['County'])

#if select == 'County':
st.write(original_data.query('Prevalent_Cases >=1')[["Province_State", "6/10/20"]].sort_values(by = ['6/10/20'], ascending=False).dropna(how='any')[:5])


if st.checkbox("Show Raw Data", False):
    st.subheader("Raw Data")
    st.write(data)
