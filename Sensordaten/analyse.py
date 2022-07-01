import pandas as pd 
import plotly.express as px
import plotly.graph_objects as go

df = pd.read_csv('channel.csv')
print(df)
df = df.drop(['entry_id', 'field3','field4'], axis=1)
df.rename(columns={'field1':'Temp', 'field2':'Hum'}, inplace=True)
print(df)

# Aggregation Data
df_agg = df.agg(['min','max','mean', 'std','var'])
print(df_agg)


fig = px.line(df, x='created_at', y=df.columns)
fig.show()